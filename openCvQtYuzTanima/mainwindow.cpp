#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    media = new QMediaPlayer(this);
    media->setMedia(QUrl("C:/Users/samar/Desktop/ses/uyarı.mp3"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//***********************************************************************************
void MainWindow::on_kamera_Ac_clicked()
{
    cap.open(0);
    if(!cap.isOpened())
    {
     cout<<"Kamera Acilmadi!"<<endl;
    }
    else
    {
     cout<<"Kamera Acildi."<<endl;

     connect(timer,SIGNAL(timeout()),this,SLOT(guncelle()));
     timer->start(20);
    }
}
//***********************************************************************************
void MainWindow::on_kamera_Kapat_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(guncelle()));
    cap.release();

yansitma(image);

     cout<<"Kamera Kapandı."<<endl;
}
//***********************************************************************************
void MainWindow::guncelle()
{
    cap >> frame;

    yuz.load("C:/OpencvQTt/opencv-3.4.3/source/data/haarcascades/haarcascade_frontalface_alt.xml");

    yuz.detectMultiScale(frame, yuz_tanima, 1.1, 2,  0|CV_HAAR_SCALE_IMAGE,cv::Size(frame.cols/4, frame.rows/4));
    cvtColor(frame, frame, CV_BGR2RGB);
    for( size_t i = 0; i < yuz_tanima.size(); i++)
    {
        cap.retrieve(frame);

    rectangle(frame, yuz_tanima[i].tl(),yuz_tanima[i].br(), cv::Scalar( 12, 50, 245 ),2);
    string frameNumberString = "TRUE";
    putText(frame, frameNumberString, cv::Point(50, 15), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,0));



}
    if(yuz_tanima.empty()){
           media->play();
        string frameNumberString2 = "FALSE";
        putText(frame, frameNumberString2, cv::Point(50, 15), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
    }

yansitma(frame);


}
//***********************************************************************************
void MainWindow::yansitma(Mat &image)
{

    cvtColor(image, image, CV_BGR2RGB);


    qt_image = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_image));
    ui->label->resize(ui->label->pixmap()->size());

}
//***********************************************************************************
