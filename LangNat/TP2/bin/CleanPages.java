import info.bliki.wiki.filter.PlainTextConverter;
import info.bliki.wiki.model.WikiModel;
import java.util.*;
import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;
import org.apache.commons.lang3.*;

public class CleanPages {

    public static void main(String[] args) {
        WikiModel wikiModel = new WikiModel("http://www.mywiki.com/wiki/${image}", "http://www.mywiki.com/wiki/${title}");
        try {
            //FileInputStream f = new FileInputStream( args[1] );
            List<String> fileLines = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
            String fileContent = "";
            for( String line: fileLines ) {
                //if( !line.startsWith("=") && !line.endsWith("=") && line.trim().length() > 0 ) {
                    fileContent = fileContent + line + "\n";//StringUtils.join(fileLines,"\n");
                //}
            }
            //System.out.println( fileContent );

            String plainStr = wikiModel.render(new PlainTextConverter(true), fileContent);
            for( String line : plainStr.split("\n") ) {
                if( line.trim().length() > 5 && !line.startsWith("<") && line.trim().endsWith(".") && !line.contains("|")) {
                    System.out.println( line );
                }
                else {
                    //System.err.println( "FILTEROUT: " + line );
                }
            }

        }
        catch( FileNotFoundException fnfEx ) {
            System.err.println( "Error: File not found! " + args[0] );
        }
        catch( IOException ioEx )  {
            System.err.println( "Something went wrong in reading or writing the file " + args[0] );
        }
    }
}
