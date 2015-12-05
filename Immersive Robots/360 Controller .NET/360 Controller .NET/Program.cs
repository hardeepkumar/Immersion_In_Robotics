using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using SharpDX;


namespace _360_Controller.NET
{
    class UDP
    {
        private UdpClient client;
        private string ipaddress;
        private int portnumber;
        private Byte[] sendbyte;

        public string IpAddress
        {
            get { return ipaddress; }
            set { ipaddress = value; }
        }

        public int portNumber
        {
            get { return portnumber; }
            set { portnumber = value; }
        }

        public UDP(string address, int port)
        {
            ipaddress = address;
            portnumber = port;
        }

        public void StartConnection()
        {
            client = new UdpClient(ipaddress, portnumber);
        }

        public void SendMessage(string message)
        {
            sendbyte = Encoding.ASCII.GetBytes(message);
            client.Send(sendbyte, sendbyte.Length);
        }

        public void EndConnection()
        {
            client.Close();
        }

    }

    class Controller
    {
        private SharpDX.XInput.UserIndex index;
        private SharpDX.XInput.Controller gamepad;
        private SharpDX.XInput.State state;

        public Controller()
        {
            index = SharpDX.XInput.UserIndex.One;
            gamepad = new SharpDX.XInput.Controller(index);
            state = gamepad.GetState();
        }

        public SharpDX.XInput.State State
        {
            get { return state = gamepad.GetState(); }
        }

    }

    class Calculate
    {
        private short lx;
        private short ly;
        private short rx;
        private short ry;
        private List<short> values;
        private string command;

        private short slop = 6500;
        private short offset = 363;
        private short inverse = 90;

        public short LX { get { return lx; } set { lx = value; } }
        public short LY { get { return ly; } set { ly = value; } }
        public short RX { get { return rx; } set { rx = value; } }
        public short RY { get { return ry; } set { ry = value; } }
        public string Command { get { return command; } }
        public List<short> Values { get { return values; } }

        public Calculate()
        {
            values = new List<short>();
            values.Add(lx);
            values.Add(ly);
            values.Add(rx);
            values.Add(ry);
        }

        public void Convert()
        {
            values[0] = lx;
            values[1] = ly;
            values[2] = rx;
            values[3] = ry;
            
                for (int i = 0; i < values.Count; i++)
                {
                    if (values[i] < -slop)
                    {
                        values[i] = (short)(inverse - (-values[i] / offset));
                    }
                    else if (values[i] > slop)
                    {
                        values[i] = (short)(values[i] / offset + inverse);
                    }
                    else
                    {
                        values[i] = inverse;
                    }
                }

            command = values[0] + "," + values[1] + "," + values[2] + "," + values[3];

        }
    }
        class Program
        {
            static void Main(string[] args)
            {
                
                UDP client_one = new UDP("10.50.6.145", 3089);
                Controller gamepad = new Controller();
                Calculate converter = new Calculate();

                client_one.StartConnection();

               

           while(true)
           {
               Console.WriteLine("Left Thumb X = {0}", gamepad.State.Gamepad.LeftThumbX);
               Console.WriteLine("Right Thumb X = {0}", gamepad.State.Gamepad.RightThumbX);
               Console.WriteLine("Left Thumb Y = {0}", gamepad.State.Gamepad.LeftThumbY);
               Console.WriteLine("RIght Thumb Y = {0}", gamepad.State.Gamepad.RightThumbY);

               converter.LX = gamepad.State.Gamepad.LeftThumbX;
               converter.LY = gamepad.State.Gamepad.LeftThumbY;
               converter.RX = gamepad.State.Gamepad.RightThumbX;
               converter.RY = gamepad.State.Gamepad.RightThumbY;

               converter.Convert();
               client_one.SendMessage(converter.Command);
               
               System.Threading.Thread.Sleep(250);
           }



            





                Console.ReadLine();
            }

            
        }
    }

