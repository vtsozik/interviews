import java.util.*;

public class onedarraypart2 {

public static boolean canWin(int pos, int[] v, int leap, int[] game)
{
    int n = game.length;
    if (pos >= n)
    {
        return true;
    }
    if (pos < 0 || game[pos] > 0 || v[pos] >= 3)
    {
        return false;
    }
    ++v[pos];
    return canWin(pos + leap, v, leap, game) || canWin(pos + 1, v, leap, game) || canWin(pos - 1, v, leap, game);
}

public static boolean canWin(int leap, int[] game) {
	int v[] = new int[game.length];
        return canWin(0, v, leap, game);
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int q = scan.nextInt();
        while (q-- > 0) {
            int n = scan.nextInt();
            int leap = scan.nextInt();
            
            int[] game = new int[n];
            for (int i = 0; i < n; i++) {
                game[i] = scan.nextInt();
            }

            System.out.println( (canWin(leap, game)) ? "YES" : "NO" );
        }
        scan.close();
    }
}
