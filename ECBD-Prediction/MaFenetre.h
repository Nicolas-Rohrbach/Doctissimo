#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QtWidgets>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QTableWidget>
#include <QLineEdit>
#include <string>
#include <vector>
#include<fstream>

typedef std::vector <std::string> CVString;
typedef std::vector <std::vector<std::string>> CMatString;

class MaFenetre : public QMainWindow
{
    Q_OBJECT // Macro OBLIGATOIRE

public slots :
    void setQuitter();
    void setCouleur();
    void setPrediction();
    void addCSV();
    void addInForm(QString str);
    double calculScore(std::string maladie, std::string sym1, std::string sym2, std::string sym3);
    double calculFreq(std::string str);
    double calculConf(std::string str, std::string targ, unsigned col);

public :
    MaFenetre(QWidget *parent = 0);
private :
    QLabel *m_lab, *m_tra, *m_labe, *m_label, *m_labT, *m_texte;
    QPushButton *m_bou, *m_bouPred, *m_bouAdd;
    QComboBox *m_com, *m_comb, *m_combo;
    QString couleur;
    CVString m_vet;
    CMatString m_mat;
    QTableWidget *m_tab, *m_tabN;
    QLineEdit *m_ligne, *m_ligne2, *m_ligne3, *m_ligne4, *m_ligne5;
};

#endif // MAFENETRE_H
