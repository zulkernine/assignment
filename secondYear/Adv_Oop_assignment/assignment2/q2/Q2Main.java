import java.util.Scanner;

public class Q2Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        double val;
        System.out.print("Value in km: ");
        val = scanner.nextDouble();
        System.out.println(String.format("%f km ~= %f mile", val,Metric.toMile(val)));
        System.out.print("Value in mie: ");
        val = scanner.nextDouble();
        System.out.println(String.format("%f mile ~= %f km", val, Metric.toKilometre(val)));

        scanner.close();
    }
}

class Metric{
    private final static double conversionFactor=1.5;

    public static double toMile(double km){
        return (km/conversionFactor) ;
    }

    public static double toKilometre(double mile){
        return (mile*conversionFactor);
    }
}
