package org.gwtbook.client;

import java.util.*;
import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.ClickListener;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;

import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.RequestCallback;
import com.google.gwt.http.client.RequestException;
import com.google.gwt.http.client.Response;



class S {
    private static String s;

    S() {
        s="default";
    }
    public  void setS(String s) {
        this.s=s;
    }
    public String getS() {
        return s;
    }
    public void getPOST() {


        RequestBuilder rb = new RequestBuilder(
            RequestBuilder.POST, "/chirico/bubble.php");

        rb.setHeader("Content-type",
                     "application/x-www-form-urlencoded");
        rb.setUser("mikem");
        rb.setPassword("some");
        rb.setTimeoutMillis(500);

        try {
            Request request = rb.sendRequest("term=GWT+in+Action",
            new RequestCallback() {
                public void
                onResponseReceived (Request req, Response res) {
                    setS(res.getText());

                }
                public void onError(Request req, Throwable exception) {

                }
            });
        } catch (RequestException e) {

        }
    }
}
/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */

public class mTest implements EntryPoint {
    final TextBox text = new TextBox();
    final S s = new S();

    private class MyResponseTextHandler implements RequestCallback {
        public void onError(Request request, Throwable exception) {

        }

        public void onResponseReceived(Request request, Response response) {
            String responseText = response.getText();
            text.setText(responseText);

        }
    }







    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {
        Image img = new Image("http://code.google.com/webtoolkit/logo-185x175.png");
        s.setS("Extra class");

        Button button = new Button(s.getS());
        s.setS("Button2");
        Button button2 = new Button(s.getS());
        s.setS("Clear");
        Button clear = new Button(s.getS());
        text.setText("Sample");



        RequestBuilder rb = new RequestBuilder(
            RequestBuilder.POST, "/chirico/bubble.php");

        rb.setHeader("Content-type",
                     "application/x-www-form-urlencoded");
        rb.setUser("mikem");
        rb.setPassword("some");
        rb.setTimeoutMillis(500);

        try {
            Request request = rb.sendRequest("term=GWT+in+Action",
            new RequestCallback() {
                public void
                onResponseReceived (Request req, Response res) {
                    text.setText(res.getText());

                }
                public void onError(Request req, Throwable exception) {

                }
            });
        } catch (RequestException e) {

        }




        VerticalPanel vPanel = new VerticalPanel();
        // We can add style names.
        vPanel.addStyleName("widePanel");
        vPanel.setHorizontalAlignment(VerticalPanel.ALIGN_LEFT);
        //    vPanel.add(img);
        vPanel.add(button);
        vPanel.add(button2);
        vPanel.add(clear);
        vPanel.add(text);

        // Add image and button to the RootPanel
        RootPanel.get().add(vPanel);

        // Create the dialog box
        final DialogBox dialogBox = new DialogBox();
        dialogBox.setText("Welcome to GWT!");
        dialogBox.setAnimationEnabled(true);
        Button closeButton = new Button("close");
        VerticalPanel dialogVPanel = new VerticalPanel();
        dialogVPanel.setWidth("100%");
        dialogVPanel.setHorizontalAlignment(VerticalPanel.ALIGN_LEFT);
        dialogVPanel.add(closeButton);

        closeButton.addClickListener(new ClickListener() {
            public void onClick(Widget sender) {
                dialogBox.hide();
            }
        });

        // Set the contents of the Widget
        dialogBox.setWidget(dialogVPanel);

        button.addClickListener(new ClickListener() {
            public void onClick(Widget sender) {
                text.setText("1onClick");
                //dialogBox.center();
                //dialogBox.show();
            }
        });

        button2.addClickListener(new ClickListener() {
            public void onClick(Widget sender) {
                s.getPOST();
                text.setText(s.getS());
                //dialogBox.center();
                //dialogBox.show();
            }
        });

        clear.addClickListener(new ClickListener() {
            public void onClick(Widget sender) {
                text.setText("");
                //dialogBox.center();
                //dialogBox.show();
            }
        });
    }
}
