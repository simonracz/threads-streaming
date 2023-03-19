import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class JavaDomains {
    public static void main(String[] args) {
        List<String> urls = new ArrayList<>();
        urls.add("https://www.example.com");
        urls.add("https://www.google.com");
        urls.add("https://www.kpn.com");

        List<Integer> statuses = new ArrayList<>();

        for (String url : urls) {
            try {
                URL obj = new URL(url);
                HttpURLConnection con = (HttpURLConnection) obj.openConnection();
                con.setRequestMethod("GET");

                int responseCode = con.getResponseCode();
                statuses.add(responseCode);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Status codes:");
        for (int status : statuses) {
            System.out.println(status);
        }
    }
}

