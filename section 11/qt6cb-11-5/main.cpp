/*
    What
    Disconnecting

    Why
    We want to disconnect a signal from a slot

    How
    Use the disconnect function
    This also talks about the connection types
*/

#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include "radio.h"
#include "station.h"

using namespace std;
bool ON=0,OFF=0,TEST=0;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Radio boombox;
    Station* channels[3];

    //create some stations
    channels[0] = new Station(&boombox,94,"Rock and Roll");
    channels[1] = new Station(&boombox,87,"Hip Hop");
    channels[2] = new Station(&boombox,104,"News");

    boombox.connect(&boombox,&Radio::quit,&a, &QCoreApplication::quit,Qt::QueuedConnection); //flaw


//    for(int i = 0; i< 3; i++)
//    {
//        Station* channel = channels[i];
//        boombox.connect(channel,&Station::send,&boombox, &Radio::listen);
//    }

    do
    {
        qInfo() << "Enter on, off, test or quit";
        QTextStream qtin(stdin);
        QString line = qtin.readLine().trimmed().toUpper();

        if((line == "ON") && (ON==false))
        {
            qInfo() << "Turning the radio on";
            for(int i = 0; i< 3; i++)
            {
                //Station* channel = channels[i];
                ON=true;OFF=false;TEST=false;

                boombox.connect(channels[i],&Station::send,&boombox, &Radio::listen);
            }
            qInfo() << "Radio is on";
        }

        if((line == "OFF")&&(OFF==false))
        {
            qInfo() << "Turning the radio off";
            for(int i = 0; i< 3; i++)
            {
                //*Station* channel = channels[i];
                OFF=true;ON=false;TEST=false;
                boombox.disconnect(channels[i],&Station::send,&boombox, &Radio::listen);
            }
            qInfo() << "Radio is off";
        }

        if((line == "TEST")&&(TEST==false))
        {
            qInfo() << "Testing";
            for(int i = 0; i< 3; i++)
            {
               /* Station* channel = channels[i];*/
                TEST=true;OFF=false;ON=false;
                channels[i]->broadcast("Broadcasting live!");
            }
            qInfo() << "Test complete";
        }

        if(line == "QUIT")
        {
            qInfo() << "Quitting";
            TEST=false;OFF=false;ON=false;
            emit boombox.quit();
            break;
        }


    } while(true);


    return a.exec();
}
