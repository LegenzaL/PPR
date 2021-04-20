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
            string data = null;
            int listenPort = 20000;
            UdpClient listener = new UdpClient(listenPort);
            IPEndPoint groupEP = new IPEndPoint(IPAddress.Any, listenPort);

            try
            {
                while (true)
                {
                    Console.WriteLine("Port 20000 - waiting for a connection...");

                    byte[] bytes = listener.Receive(ref groupEP);

                    Console.WriteLine($"Port 20000 - received from {groupEP} :\n"); 
                    data = BitConverter.ToString(bytes);

                    string path = Thread.CurrentThread.ManagedThreadId + ".txt";

                    Console.WriteLine($"Data in: {path}"); 
                    using (StreamWriter sw = File.CreateText(path))
                    {
                        sw.WriteLine(data);
                    }
                }
            }
            catch (SocketException e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                listener.Close();
            }

        }

        static void client2()
        {
            string data = null;
            int listenPort = 21000;
            UdpClient listener = new UdpClient(listenPort);
            IPEndPoint groupEP = new IPEndPoint(IPAddress.Any, listenPort);

            try
            {
                while (true)
                {

                    Console.WriteLine("Port 21000 - waiting for a connection...");

                    byte[] bytes = listener.Receive(ref groupEP);

                    Console.WriteLine($"Port 21000 - received from {groupEP} :\n"); 
                    data = BitConverter.ToString(bytes);

                    string path = Thread.CurrentThread.ManagedThreadId + ".txt";

                    Console.WriteLine($"Data in: {path}");
                    using (StreamWriter sw = File.CreateText(path))
                    {
                        sw.WriteLine(data);
                    }
                }
            }
            catch (SocketException e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                listener.Close();
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