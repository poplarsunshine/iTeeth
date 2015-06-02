package jni;

import android.util.Log;


public class JniApi {

	//***********java call c++
	
	/*
	 反馈刷牙信息
	 *type 预留
	 *value 位置（0~15）
	*/
	public static native boolean androidBluetoothEvent( int type, int value);

	/*
	 *蓝牙连接状态通知
	*/
	public static native boolean androidBluetoothConnected( boolean b);

	
	//**********
	//**********c++ call java
	
	/*
	 * 设置蓝牙可用
	*/
	public static void setAndroidBluetoothEnable( boolean b )
	{
		if(b == true)
		{
			//扫描 连接设备
		}
		else
		{
			//断开连接
		}
	}
}
