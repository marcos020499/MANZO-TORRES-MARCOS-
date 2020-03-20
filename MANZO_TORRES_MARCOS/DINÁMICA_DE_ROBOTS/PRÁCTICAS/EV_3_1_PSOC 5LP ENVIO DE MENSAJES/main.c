/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <ros/ros.h>
#include <string>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int str_counter (char *str){
  int counter = 0;
  while(*str++){
    counter++;
  }

  return counter;
}

int main(int argc, char **argv){
  std::string dev = "/dev/ttyACM0",str_str;
  int baudrate = B9600;

  char str[64] = "Hello ROS & PSoC";

  ros::init(argc, argv, "UART_comm");

  ros::NodeHandle arg_nh("~");
  ros::NodeHandle nh;

  arg_nh.getParam("device", dev);
  arg_nh.getParam("baudrate", baudrate);
  arg_nh.getParam("message",str_str);

  strcpy(str,str_str.c_str());

//-------シリアルポート設定-------------------------
      int fd;                           /* ファイルディスクリプタ */
      struct termios oldtio, newtio;    /* シリアル通信設定 */
      int baudRate = B57600;
      fd = open(dev.c_str(), O_RDWR);   /* デバイスをオープンする */

      ioctl(fd, TCGETS, &oldtio);       /* 現在のシリアルポートの設定を待避させる */
      newtio = oldtio;                  /* ポートの設定をコピー */
      newtio.c_cflag = baudRate | CS8 | CREAD;
  	  newtio.c_iflag = IGNPAR | ICRNL;
  	  newtio.c_oflag = 0;
  	  newtio.c_lflag = 0;          /* ポートの設定をおこなう 詳細はtermios参照 */
      ioctl(fd, TCSETS, &newtio);       /* ポートの設定を有効にする */
//--------------------------------------------------------

  while(ros::ok()){

    printf("%s\n%d\n",str, str_counter(str));

    if(str_counter(str)>64){
      ROS_INFO("Warning!! \nThe amount of data that PSoC5 can receive is up to 64bytes.");
      //PSoC5のUSBUARTは一度に最大64バイトまでしか受け付けない。
    }

    if(fd<0){
      ROS_INFO("Error ! serialport open error!");
      return -1;
    }



    write(fd,str,sizeof(str)); //送信

    ros::spinOnce();

  }
  ioctl(fd, TCSETS, &oldtio);       /* ポートの設定を元に戻す */
  close(fd);                        /* デバイスのクローズ */

  return 0;
}