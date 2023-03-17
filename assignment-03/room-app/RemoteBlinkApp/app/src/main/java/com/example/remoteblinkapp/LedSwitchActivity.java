package com.example.remoteblinkapp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.Button;
import android.widget.SeekBar;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

@SuppressLint("MissingPermission")
public class LedSwitchActivity extends AppCompatActivity {

    private class SeekBarListener implements SeekBar.OnSeekBarChangeListener {

        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        }

        public void onStartTrackingTouch(SeekBar seekBar) {}

        public void onStopTrackingTouch(SeekBar seekBar) {
            sendMessage(1);
        }

    }

    private OutputStream bluetoothOutputStream;
    private Button remoteButton;
    private SeekBar remoteBar;
    private boolean ledState;
    private BluetoothClientConnectionThread connectionThread;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_led_switch);
        ledState = false;

        initUI();
    }

    private void initUI() {
        remoteButton = findViewById(R.id.remotebutton);
        remoteButton.setBackgroundColor(Color.LTGRAY);
        remoteButton.setEnabled(false);
        remoteButton.setOnClickListener((v) -> sendMessage(0));

        remoteBar = findViewById(R.id.remotebar);
        remoteBar.setEnabled(false);
        remoteBar.setOnSeekBarChangeListener(new SeekBarListener());



    }

    private void sendMessage(int source) {
        new Thread(() -> {
            try {
                String message = "";
                if(source == 0) {
                    message = ledState ? "off\n" : "on\n";

                    ledState = !ledState;
                    runOnUiThread(() -> {
                        remoteButton.setBackgroundColor(ledState? Color.GREEN : Color.DKGRAY);
                        remoteButton.setText(ledState? "Turn Off" : "Turn On");
                    });
                }
                else if(source == 1) message = Integer.toString(remoteBar.getProgress()) + "\n";
                else if(source == 2) message = "remote on\n";
                else if(source == 3) message = "remote off\n";

                bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    @Override
    protected void onStart() {
        super.onStart();
        Intent intent = getIntent();
        BluetoothDevice bluetoothDevice = intent.getParcelableExtra(ScanActivity.X_BLUETOOTH_DEVICE_EXTRA);
        BluetoothAdapter btAdapter = getSystemService(BluetoothManager.class).getAdapter();
        Log.i(C.TAG, "Connecting to " + bluetoothDevice.getName());
        connectionThread = new BluetoothClientConnectionThread(bluetoothDevice, btAdapter, this::manageConnectedSocket);
        connectionThread.start();
    }

    private void manageConnectedSocket(BluetoothSocket socket) {
        try {
            bluetoothOutputStream = socket.getOutputStream();
            Log.i(C.TAG, "Connection successful!");
            sendMessage(2);

        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }
        runOnUiThread(() -> {
            remoteButton.setEnabled(true);
            remoteButton.setBackgroundColor(ledState? Color.GREEN : Color.DKGRAY);
            remoteButton.setText(ledState? "Turn Off" : "Turn On");
            remoteBar.setEnabled(true);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        sendMessage(3);
        connectionThread.cancel();
    }

}