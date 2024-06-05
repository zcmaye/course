#include <iostream>
#include <quazip/JlCompress.h>
#include <QFile>
#include <QCoreApplication>


void test_quazip()
{
    //压缩文件
    if (!JlCompress::compressFile("test_dir/xxx.zip","test_dir/hello world.txt")) {
        printf("压缩失败！\n");
    }
    //压缩多个文件
    if (!JlCompress::compressFiles("test_dir/xxxs.zip", {"test_dir/hello world.txt","test_dir/one.txt"})) {
        printf("压缩失败！\n");
    }
    //从压缩包中解压指定的文件hello world.txt 并解压到test_dir/maye.txt
    auto filename = JlCompress::extractFile("test_dir/xxx.zip", "hello world.txt","test_dir/maye.txt");
    if (filename.isEmpty()) {
        printf("解压文件失败！\n");
    }
    
    //压缩文件夹
    //if (!JlCompress::compressDir("test_dir/QuaZip.zip","test_dir/QuaZip")) {
    //    printf("压缩失败！\n");
    //}

    //解压到指定目录目录
    //auto filelist = JlCompress::extractDir("test_dir/QuaZip.zip","test_dir/QuaZip");
    //if (filelist.isEmpty()) {
    //    printf("解压失败！\n");
    //}
    //else {
    //    qInfo() << filelist;
    //}

    QFile file("test_dir/QuaZip.zip");
    if (!file.open(QIODevice::ReadOnly)) {
        qInfo() << "open failed";
    }
    auto file_list  = JlCompress::extractDir(&file, "test_dir/QuaZip");
    if (!file_list.isEmpty()) {
		printf("解压失败！\n");
    }

    qInfo()<<"encoding"<< QStringDecoder::encodingForName("WINDOWS-1251").value_or(QStringConverter::System);
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    system("chcp 65001");
    test_quazip();
    //return a.exec();
    return 0;
}
