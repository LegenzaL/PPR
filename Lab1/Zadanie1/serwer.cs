using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace socket
{
    class Program
    {
        static void Main(string[] args)
        {
			byte[] bytes = new Byte[1024];
			string data = null;
            
			IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, 20000);
			Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp );
			try {
				listener.Bind(localEndPoint);
				listener.Listen(10); 
				while (true) {
					try{
						Console.WriteLine("Waiting for a connection...");
						Socket handler = listener.Accept();
						Console.WriteLine($"Connection from {handler.RemoteEndPoint.ToString()}");

                        handler.Receive(bytes);
                        data = BitConverter.ToString(bytes);


						Console.WriteLine($"Received: {data}");
						handler.Send(bytes);
						handler.Shutdown(SocketShutdown.Both);
						handler.Close();
					} catch (Exception e) {
						Console.WriteLine(e.ToString());
					}
				}
			} catch (Exception e) {
				Console.WriteLine(e.ToString());
			}
			Console.WriteLine("\nPress ENTER to continue...");
			Console.Read();
        }
    }
}
