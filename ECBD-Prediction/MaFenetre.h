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

public :
    MaFenetre(QWidget *parent = 0);
private :
    QLabel *m_lab, *m_tra, *m_labe, *m_label;
    QPushButton *m_bou;
    QComboBox *m_com, *m_comb, *m_combo;
    QString couleur;
    CVString m_vet;
    CMatString m_mat;

};

#endif // MAFENETRE_H
