import java.net.*;
import java.io.*;

public class Client {

    public static void main(String[] args) throws Exception {
        String host = args[0];          // adresa IP sau numele domeniului
        int port = Integer.parseInt(args[1]);  // portul
        Socket c = new Socket(host, port);

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("sir = ");
        String sir = reader.readLine();

        PrintWriter socketOut = new PrintWriter(c.getOutputStream(), true);
        BufferedReader socketIn = new BufferedReader(new InputStreamReader(c.getInputStream()));
        
        socketOut.println(sir);
        String raspuns = socketIn.readLine();

        System.out.println("Am primit de la server: " + raspuns);

        reader.close();
        c.close();
    }
}