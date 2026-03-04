import java.net.*;
import java.util.Arrays;

public class Server {
public static void main(String args[]) throws Exception {
    ServerSocket s = new ServerSocket(1234);
    byte b[] = new byte[100];

    while(true) {
        Socket c = s.accept();
        System.out.println("Client connected!");
        c.getInputStream().read(b);
        String sir = new String(b).trim();
        String oglidnit = new StringBuilder(sir).reverse().toString();
        c.getOutputStream().write(oglidnit.getBytes());

        Arrays.fill(b, (byte)0);
        c.close();
    }
}
}
