#include <QDebug>
#include <QGenericMatrix>
#include <QtGui/QImage>
#include <QTextStream>
//---------------------------------------------------------------------------------------

const QString ASCII_BRIGHTNESS = "`-\"^:;!iIl~+?][}{1)\(|/t2fjrxnuvczXYUJCLQO09Zmwqpdbkhao*#MW8%B@$";

QTextStream out(stdout);
QTextStream in(stdin);
QString imageSize(const QImage& a_img);
QVector<QVector<int>> getBrightnessMatrix(const QImage& a_img);
void printASCIIArt(const QVector<QVector<int>>& a_matrix);
//---------------------------------------------------------------------------------------

int main()
{
    out << "Please enter a path to the file:" << endl;
    QString filePath;
    in >> filePath;
    QImage img(filePath);
//    img.scaled(85,85,Qt::KeepAspectRatio);

    if (!img.isNull()) { out << "Image loaded successfully!" << endl; }
    else { out << "Image not loaded." << endl; return -1; }
    out << imageSize(img) << endl;

    out << "ASCII_BRIGHTNESS.size() = " << ASCII_BRIGHTNESS.size() << endl;

    auto pixelsMatrix = getBrightnessMatrix(img);
    printASCIIArt(pixelsMatrix);

    return 0;
}
//---------------------------------------------------------------------------------------

QString imageSize(const QImage& a_img) {
    int width = a_img.width();
    int height = a_img.height();
    return "Image size " + QString::number(width) + " x " + QString::number(height);
}

QVector<QVector<int>> getBrightnessMatrix(const QImage& a_img)
{
    int width = a_img.width();
    int height = a_img.height();

    QVector<QVector<int>> matrix(height);
    for (int row = 0; row < height; ++row) {
        matrix[row].resize(width);
        for (int column = 0; column < width; ++column) {
            QRgb pix = a_img.pixel(column, row);
            matrix[row][column] = (qRed(pix) + qGreen(pix) + qBlue(pix)) / 3;
        }
    }
    return matrix;
}

void printASCIIArt(const QVector<QVector<int>>& a_matrix)
{
    const int height = a_matrix.size();
    for (int row = 0; row < height; ++row) {
        QString line;
        for (int column = 0; column < a_matrix[row].size(); ++column) {
            int brightness = a_matrix[row][column] / (255 / ASCII_BRIGHTNESS.size());
            if (brightness > 0) brightness -= 1;
            QChar ch = ASCII_BRIGHTNESS[brightness];
            line.push_back(ch); line.push_back(ch);// line.push_back(ch);
        }
        out << line << endl;
    }
}
