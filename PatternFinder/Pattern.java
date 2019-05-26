package pattern;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;


public class Pattern {
    static String p = readFileAsString("wzorzec.txt");
    static String t = readFileAsString("tekst.txt");
    static int m = p.length();
    static int n = t.length();

    static void naive(String P, String T) {
 

        for (int s = 0; s < n - m; s++) {

            int j;

            for (j = 0; j < m; j++)
                if (T.charAt(s + j) != P.charAt(j))
                    break;
            if (j == m)
                System.out.println("znalezione wystąpienie wzorca od pozycji: " + (s + 1));
        }

    }
    static void rabinKarp(String P, String T, int d, int q) {
        int h = 1;

        for (int i = 0; i < m - 1; i++)
            h = (h * d) % q;

        int p = 0;
        int t = 0;

        for (int i = 0; i < m; i++) {
            p = (d * p + P.charAt(i)) % q;
            t = (d * t + T.charAt(i)) % q;
        }

        for (int s = 0; s <= n - m; s++) {

            if (p == t) {
                int j;
                for (j = 0; j < m; j++) {
                    if (T.charAt(s + j) != P.charAt(j))
                        break;
                }

                if (j == m)
                    System.out.println("znalezione wystąpienie wzorca od pozycji: " + (s + 1));
            }

            if (s < n - m) {
                t = (d * (t - T.charAt(s) * h) + T.charAt(s + m)) % q;
                if (t < 0)
                    t = (t + q);
            }
        }
    }


    public static void KMP(String P, String T) {

        int pi[] = new int[m];
        int q = 0;
        prefixFunction(P, pi);

        for (int i = 0; i < n; i++) {
            while (q > 0 && P.charAt(q) != T.charAt(i)) {
                q = pi[q];
            }
            if (P.charAt(q) == T.charAt(i)) {
                q++;
            }
            if (q == m) {
                System.out.println("znalezione wystąpienie wzorca od pozycji: " + (i - m + 2));
                q = pi[q - 1];
            }
        }
    }

    static void prefixFunction(String P, int pi[]) {
        pi[0] = 0;
        int k = 0;
        for (int q = 2; q < m; q++) {
            while (k > 0 && P.charAt(k + 1) != P.charAt(q)) {
                k = pi[k];
            }
            if (P.charAt(k + 1) == P.charAt(q)) {
                k = k + 1;
            }
            pi[q] = k;
        }
    }


    static String readFileAsString(String fileName) {
        String text = "";
        try {
            text = new String(Files.readAllBytes(Paths.get(fileName)));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return text.replaceAll("\\s", "");
    }


    public static void main(String[] args) {

        long start, end, timediff1, timediff2, timediff3;
        int timediff[]=new int[100];

        
        System.out.println("---ALGORYTM NAIWNY---\n");
        start = System.currentTimeMillis();
        naive(p, t);
        end = System.currentTimeMillis();
        timediff1 = end - start;

        System.out.println("\n---ALGORYTM RABINA KARPA---\n");

        start = System.currentTimeMillis();
        rabinKarp(p, t, 4, 27077);
        end = System.currentTimeMillis();
        timediff2 = end - start;
        System.out.println("\n---ALGORYTM KMP---\n");

        start = System.currentTimeMillis();
        KMP(p, t);
        end = System.currentTimeMillis();
        timediff3 = end - start;

        System.out.println("\nCzas algorytmu naiwnego:" + timediff1 + " ms");
        System.out.println("Czas algorytmu Rabina-Karpa:" + timediff2 + " ms");
        System.out.println("Czas algorytmu KMP:" + timediff3 + " ms");

    }

}