package fr.licinfo;

import javax.swing.*;

/**
 * Hello world!
 *
 */
public class App
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );

        JFrame jFrame = new JFrame();

        JPanel jPanel = new Picture();

        jFrame.setContentPane(jPanel);

        jFrame.setVisible(true);
        jFrame.setSize(500, 500);
    }
}
