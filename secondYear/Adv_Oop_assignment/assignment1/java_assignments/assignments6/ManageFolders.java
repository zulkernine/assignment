package java_assignments.assignments6;

import java.io.File;

public class ManageFolders {
    private static boolean foldersCreated;

    static{
        foldersCreated = false;
        File hospitalDir = new File("./hospital");
        if(hospitalDir.exists()){
            foldersCreated = true;
        }
    }


    public static void checkFolders(){
        if(!foldersCreated){
            File hospitalDir = new File("./hospital");
            hospitalDir.mkdir();

            File doctorDir = new File("./hospital/doctor");
            doctorDir.mkdir();

            File patientDir = new File("./hospital/patient");
            patientDir.mkdir();
            foldersCreated = true;
        }
    }

    public static String patientFoldersPath(){
        return "./hospital/patient/";
    }

    public static String doctorFoldersPath() {
        return "./hospital/doctor/";
    }
}
