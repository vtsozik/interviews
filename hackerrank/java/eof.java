import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class eof {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner scan = new Scanner(System.in);
	int i = 0;
        while(scan.hasNextLine())
	{
	    String s = scan.nextLine();
	    System.out.printf("%d %s\n", ++i, s);
	}
	scan.close();
    }
}
