#ifndef IMAGEEXPLICATIF_H
#define IMAGEEXPLICATIF_H

#include <QApplication>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class ImageExplicatif : public QWidget
{
public:
    ImageExplicatif();

    inline void setImage(QString image) {
                                          imageLab->setPixmap(QPixmap(image));
                                        }

private:
    QLabel *imageLab;
};

#endif // IMAGEEXPLICATIF_H
