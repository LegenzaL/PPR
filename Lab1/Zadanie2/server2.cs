using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace socket
{
    class Program
    {
        static void client1()
        {
            byte[] bytes = new Byte[1024];
            string data = null;

            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, 20000);
            Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            while (true)
            {
                try
                {
                    listener.Bind(localEndPoint);
                    listener.Listen(10);
                    //Console.WriteLine("Waiting for a connection...");
                    while (true)
                    {
                        try
                        {
                            Console.WriteLine("Port 20000 - waiting for a connection...");
                            Socket handler = listener.Accept();
                            Console.WriteLine($"Port 20000 - connection from {handler.RemoteEndPoint.ToString()}");
                            handler.Receive(bytes);
                            data = BitConverter.ToString(bytes);

                            //Console.WriteLine($"Port 20000 - received from {handler.RemoteEndPoint.ToString()}: \n{data}");
                            //string path = @"client1.txt";


                            string path = Thread.CurrentThread.ManagedThreadId + ".txt";
                            Console.WriteLine($"Port 20000 - recived data, data in: {path}"); 

                            using (StreamWriter sw = File.CreateText(path))
                            {
                                sw.WriteLine(data);
                            }

                            handler.Send(bytes);
                            handler.Shutdown(SocketShutdown.Both);
                            handler.Close();

                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e.ToString());
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
                Console.WriteLine("\nPress ENTER to continue...");
                Console.Read();
            }
        }



        static void client2()
        {
            byte[] bytes = new Byte[1024];
            string data = null;

            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, 21000);
            Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            while (true)
            {
                try
                {
                    listener.Bind(localEndPoint);
                    listener.Listen(10);

                    while (true)
                    {
                        try
                        {
                            Console.WriteLine("Port 21000 - waiting for a connection...");
                            Socket handler = listener.Accept();
                            Console.WriteLine($"Port 21000 - connection from {handler.RemoteEndPoint.ToString()}");
                            handler.Receive(bytes);
                            data = BitConverter.ToString(bytes);

                            //Console.WriteLine($"Port 21000 - received from {handler.RemoteEndPoint.ToString()}: \n{data}");
                            //string path = @"client2.txt";


                            string path = Thread.CurrentThread.ManagedThreadId + ".txt";
                            Console.WriteLine($"Port 21000 - recived data, data in: {path}");

                            using (StreamWriter sw = File.CreateText(path))
                            {
                                sw.WriteLine(data);
                            }

                            handler.Send(bytes);
                            handler.Shutdown(SocketShutdown.Both);
                            handler.Close();
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e.ToString());
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
                Console.WriteLine("\nPress ENTER to continue...");
                Console.Read();
            }
        }

        static void Main(string[] args)
        {
            Thread th1 = new Thread(client1);
            th1.Start();

            Thread th2 = new Thread(client2);
            th2.Start();
        }
    }
}