package com.luminy;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

/**
 * Created by zT00N on 16/09/2016.
 */
public class MainFrame extends JFrame {

    private Vigenere vig;

    private JPanel panel1;
    private JTextArea textArea1;
    private JTextArea textArea4;
    private JTextField textField1;
    private JButton encodeTextButton;
    private JButton getTextFromFileButton1;
    private JButton saveTextInFileButton1;
    private JTextArea textArea3;
    private JTextField textField2;
    private JButton button1;
    private JButton saveTextInFileButton2;
    private JButton getTextFromFile2;
    private JTextArea textArea2;

    public MainFrame() {
        super("Hello world");

        setContentPane(panel1);

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        vig = new Vigenere(new File("C:\\Users\\zT00N\\IdeaProjects\\Vigenere\\res", "dictionnaire.txt"));
        setVisible(true);

        getTextFromFileButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "Fichiers texte", "txt");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showOpenDialog(panel1);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    textArea1.setText(Main.fileTextToString(chooser.getSelectedFile()));
                }
            }
        });
        getTextFromFile2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "Fichiers texte", "txt");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showOpenDialog(panel1);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    textArea2.setText(Main.fileTextToString(chooser.getSelectedFile()));
                }
            }
        });
        encodeTextButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String encoded = vig.encode(textArea1.getText(), textField1.getText());
                textArea4.setText(encoded);
                textArea2.setText(encoded);
            }
        });
        saveTextInFileButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "Fichiers texte", "txt");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showOpenDialog(panel1);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    Main.writeInFile(chooser.getSelectedFile(), textArea4.getText());
                }
            }
        });
        saveTextInFileButton2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "Fichiers texte", "txt");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showOpenDialog(panel1);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    Main.writeInFile(chooser.getSelectedFile(), textArea3.getText());
                }
            }
        });
        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String decoded = "";
                decoded = vig.decodeKey(textArea2.getText());
                textArea3.setText(vig.decodeText(textArea2.getText(), decoded));
                textField2.setText(decoded);
            }
        });
    }
}
