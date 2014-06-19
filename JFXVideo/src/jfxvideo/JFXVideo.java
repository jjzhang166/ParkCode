/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jfxvideo;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.lang.*;

/**
 *
 * @author park
 */
public class JFXVideo extends Application {
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Hello World!");
        Button btn = new Button();
        btn.setText("Say 'Hello World'");
        btn.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {
                System.out.println("Hello World!");
            }
        });
        
        Byte b = ( byte ) 0x7F;
        short s = ( short ) b;
        s &= 0xFF;
        String str = b.toString( );
        
        VideoFrame frame = new VideoFrame( );
        frame.show();
        
        return;
        //StackPane root = new StackPane();
        //root.getChildren().add(btn);
        //primaryStage.setScene(new Scene(root, 300, 250));
        //primaryStage.show();
    }
}
