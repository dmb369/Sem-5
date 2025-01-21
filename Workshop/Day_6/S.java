import java.util.Scanner;

public class S
{
    public static int mp(int[] p, int f) {
        int n = p.length;
        if (n == 0) return 0;

        int h = -p[0];  
        int nh = 0;       

        for (int i = 1; i < n; i++) 
        {
            nh = Math.max(nh, h + p[i] - f);
            h = Math.max(h, nh - p[i]);
        }

        return nh;
    }

    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);

        System.out.print("No. of days: ");
        int n = scanner.nextInt();
        int[] p = new int[n];

        System.out.print("Stock Prices: ");
        for (int i = 0; i < n; i++) p[i] = scanner.nextInt();
        
        System.out.print("Transaction Fee: ");
        int f = scanner.nextInt();

        int ans = mp(p, f);
        System.out.println("The profit is " + ans);

        scanner.close();
    }
}
