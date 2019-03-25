#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <string>
#include <vector>

typedef std::vector <std::string> CVString;
typedef std::vector <std::vector<std::string>> CMatString;

class MaFenetre : public QMainWindow
{
    Q_OBJECT // Macro OBLIGATOIRE

public slots :
    void setQuitter();
    void setCouleur();
    void setPrediction();
    QString prediction(std::string str);
    double calculFreq(std::string str);
    double calculConf(std::string str, std::string targ, std::string arg);

public :
    MaFenetre(QWidget *parent = 0);
private :
    QLabel *m_lab, *m_tra, *m_labe, *m_label;
    QPushButton *m_bou, *m_bouPred;
    QComboBox *m_com, *m_comb, *m_combo;
    QString couleur;
    CVString m_vet;
    CMatString m_mat;

};

#endif // MAFENETRE_H
