#include "MaFenetre.h"
#include "charger_csv.h"

typedef std::vector <std::string> CVString;

bool checkTab(CVString tab, std::string val) {
    for (unsigned i = 0; i < tab.size(); i++) {
        if(tab[i] == val) {
            return true;
        }
    }
    return false;
}


MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1000,1000);

    // Texte du haut
    m_texte = new QLabel("CLASSIFICATION DES PATIENTS - PREDICTION", this);
    m_texte->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_texte->adjustSize();
    m_texte->move(250,0);

    // Bouton pour quitter
    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(600,400,80,40);

    // Bouton pour prédire
    m_bouPred = new QPushButton("Prédire", this);
    m_bouPred->setGeometry(300,400,80,40);

    read_csv (m_mat, m_vet, "data.csv"); // Lecture du fichier csv

    // Affiche les choix de toux sans doublon
    m_lab = new QLabel("Fièvre", this);
    m_lab->setFont(QFont("Arial", 12, QFont::Bold, true));

    m_lab->move(200, 125);
    m_com = new QComboBox(this);
    m_com->setGeometry(200,150,100,30);
    //Ajoute et empeche les doublons
    CVString tab;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][0];
        if(! checkTab(tab,s)) {
            tab.push_back(s);
            QString qs = QString::fromUtf8(s.c_str());
            m_com->addItem(qs);
        }
    }

    // Affiche les choix de toux sans doublon
    m_labe = new QLabel("Douleur", this);
    m_labe->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_labe->move(300, 125);

    m_comb = new QComboBox(this);
    m_comb->setGeometry(300,150,100,30);
    //Ajoute et empeche les doublons
    CVString tabl;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][1];
        if(! checkTab(tabl,s)) {
            tabl.push_back(s);
            QString qs = QString::fromUtf8(s.c_str());
            m_comb->addItem(qs);
        }
    }

    // Affiche les choix de toux sans doublon
    m_label = new QLabel("Toux", this);
    m_label->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_label->move(400, 125);

    m_combo = new QComboBox(this);
    m_combo->setGeometry(400,150,100,30);
    //Ajoute et empeche les doublons
    CVString table;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][2];
        if(! checkTab(table,s)) {
            table.push_back(s);
            QString qs = QString::fromUtf8(s.c_str());
            m_combo->addItem(qs);
        }
    }

    //Label tableau
    m_labT = new QLabel(this);
    m_labT->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_labT->move(100, 500);
    m_labT->setText("Table d'apprentisage");
    m_labT->adjustSize();

    // Initialisation des 2 tableaux
    m_tab = new QTableWidget(this);
    m_tab->setRowCount(m_mat.size());
    m_tab->setColumnCount(m_vet.size());
    m_tab->setGeometry(550,550,450,300);

    m_tabN = new QTableWidget(this);
    m_tabN->setRowCount(0);
    m_tabN->setColumnCount(m_vet.size());
    m_tabN->setGeometry(0,550,550,300);

    // Initialisation des headers des colonnes
    string sympt = "Fièvre";
    QString fievre = QString::fromUtf8(sympt.c_str());
    m_tab->setHorizontalHeaderItem(0,new QTableWidgetItem(fievre));
    m_tabN->setHorizontalHeaderItem(0,new QTableWidgetItem(fievre));
    sympt = "Douleur";
    QString douleur = QString::fromUtf8(sympt.c_str());
    m_tab->setHorizontalHeaderItem(1,new QTableWidgetItem(douleur));
    m_tabN->setHorizontalHeaderItem(1,new QTableWidgetItem(douleur));
    sympt = "Toux";
    QString toux = QString::fromUtf8(sympt.c_str());
    m_tab->setHorizontalHeaderItem(2,new QTableWidgetItem(toux));
    m_tabN->setHorizontalHeaderItem(2,new QTableWidgetItem(toux));
    sympt = "Maladie";
    QString maladi = QString::fromUtf8(sympt.c_str());
    m_tab->setHorizontalHeaderItem(3,new QTableWidgetItem(maladi));
    m_tabN->setHorizontalHeaderItem(3,new QTableWidgetItem(maladi));

    // Affiche tout le fichier csv
    for (unsigned i = 0; i < m_mat.size(); i++) {
        for (unsigned j = 0; j < m_vet.size(); j++) {
            std::string s = m_mat[i][j];
            QString qs = QString::fromUtf8(s.c_str());
            m_tab->setItem(i, j, new QTableWidgetItem(qs));
        }
    }

    // Permet de donner le nom du patient lors de la prédiction
    QLabel *m_labId = new QLabel(this);
    m_labId->setFont(QFont("Arial", 10, QFont::Bold, true));
    m_labId->move(50,400);
    m_labId->setText("Nom du patient");
    m_labId->adjustSize();

    m_ligne5 = new QLineEdit(this);
    m_ligne5->setGeometry(200,400,75,25);

    // Formulaire pour ajouter une ligne dans le csv
    QLabel *m_labSymp1 = new QLabel(this);
    m_labSymp1->setFont(QFont("Arial", 10, QFont::Bold, true));
    m_labSymp1->move(700,75);
    m_labSymp1->setText("Fièvre");
    m_labSymp1->adjustSize();

    m_ligne = new QLineEdit(this);
    m_ligne->setGeometry(800,75,75,25);

    QLabel *m_labSymp2 = new QLabel(this);
    m_labSymp2->setFont(QFont("Arial", 10, QFont::Bold, true));
    m_labSymp2->move(700,100);
    m_labSymp2->setText("Douleur");
    m_labSymp2->adjustSize();

    m_ligne2 = new QLineEdit(this);
    m_ligne2->setGeometry(800,100,75,25);

    QLabel *m_labSymp3 = new QLabel(this);
    m_labSymp3->setFont(QFont("Arial", 10, QFont::Bold, true));
    m_labSymp3->move(700,125);
    m_labSymp3->setText("Toux");
    m_labSymp3->adjustSize();

    m_ligne3 = new QLineEdit(this);
    m_ligne3->setGeometry(800,125,75,25);

    QLabel *m_labMaladie = new QLabel(this);
    m_labMaladie->setFont(QFont("Arial", 10, QFont::Bold, true));
    m_labMaladie->move(700,150);
    m_labMaladie->setText("Maladie");
    m_labMaladie->adjustSize();

    m_ligne4 = new QLineEdit(this);
    m_ligne4->setGeometry(800,150,75,25);

    // Bouton pour ajouter une ligne dans le csv
    m_bouAdd = new QPushButton("Add", this);
    m_bouAdd->setGeometry(800,200,80,40);

    // Label qui affiche le résultat d'une prédiction
    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(320, 300);


    connect(m_com, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));
    connect(m_comb, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));
    connect(m_combo, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));

    connect(m_bou, SIGNAL(clicked()),
            this, SLOT(setQuitter()));

    connect(m_bouPred, SIGNAL(clicked()),
            this, SLOT(setPrediction()));

    connect(m_bouAdd, SIGNAL(clicked()),
            this, SLOT(addCSV()));

}


//Ajoute une ligne dans le csv
void MaFenetre::addCSV()
{
    QString sympt1 = m_ligne->text();
    QString sympt2 = m_ligne2->text();
    QString sympt3 = m_ligne3->text();
    QString maladie = m_ligne4->text();

    std::string sym1 = sympt1.toStdString();
    std::string sym2 = sympt2.toStdString();
    std::string sym3 = sympt3.toStdString();
    std::string maladi = maladie.toStdString();

    std::ofstream file;
    file.open("data.csv");
    file << sym1
         << ","
         << sym2
         << ","
         << sym3
         << ","
         << maladi
         << endl;
}

// Permet de quitter la fenêtre
void MaFenetre::setQuitter()
{
    exit(0);
}

void MaFenetre::setCouleur()
{
    couleur = m_com->currentText();
    m_tra->setText("");
}


// Lors d'une prédiction, ajoute les infos dans le tableau de droite
void MaFenetre::addInForm(QString str) {
    QString bout1 = m_com->currentText();
    QString bout2 = m_comb->currentText();
    QString bout3 = m_combo->currentText();

    QString nom = m_ligne5->text();
    if(nom.isEmpty()) {
        string s = "Anonyme";
        nom = QString::fromUtf8(s.c_str());
    }

    m_tabN->insertRow(m_tabN->rowCount());

    m_tabN->setItem(m_tabN->rowCount()-1, 0, new QTableWidgetItem(bout1));
    m_tabN->setItem(m_tabN->rowCount()-1, 1, new QTableWidgetItem(bout2));
    m_tabN->setItem(m_tabN->rowCount()-1, 2, new QTableWidgetItem(bout3));
    m_tabN->setItem(m_tabN->rowCount()-1, 3, new QTableWidgetItem(str));
    m_tabN->setVerticalHeaderItem(m_tabN->rowCount()-1, new QTableWidgetItem(nom));
}


// Prédit la maladie du patient
void MaFenetre::setPrediction()
{
    CVString tab;
    std::string s;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][3];
        if(! checkTab(tab,s)) {
            tab.push_back(s);
        }
    }
    double score = 0;
    std::string maladie;
    //Récupère les symptomes
    QString bout1 = m_com->currentText();
    QString bout2 = m_comb->currentText();
    QString bout3 = m_combo->currentText();
    std::string sym1 = bout1.toStdString();
    std::string sym2 = bout2.toStdString();
    std::string sym3 = bout3.toStdString();
    for(unsigned i = 0; i < tab.size(); i++) {
        double score2 = calculScore(tab[i],sym1,sym2,sym3);
        if(score < score2) {
            maladie = tab[i];
            score = score2;
        }
    }
    if(score == 0) {
        maladie = "Aucune données";
    }
    QString qs = QString::fromUtf8(maladie.c_str());
    m_tra->setText(qs);
    m_tra->adjustSize();
    addInForm(qs);
}

// Calcul le score d'une maladie en fonction des symptomes
double MaFenetre::calculScore(std::string maladie, std::string sym1, std::string sym2, std::string sym3) {
    double score = 0;
    double freq = calculFreq(maladie);
    double conf1 = calculConf(sym1,maladie,0);
    double conf2 = calculConf(sym2,maladie,1);
    double conf3 = calculConf(sym3,maladie,2);
    score = freq * conf1 * conf2 * conf3;
    return score;
}

// Calcul la fréquence d'une maladie
double MaFenetre::calculFreq(std::string str) {
    double maladie = 0;
    for(unsigned i = 0; i < m_mat.size(); i++) {
        std::string mal = m_mat[i][3];
        if(mal == str) {
            maladie = maladie + 1;
        }
    }

    return maladie/m_mat.size();
}

// Calcul la confiance d'un symptome par rapport à une maladie
double MaFenetre::calculConf(std::string str, std::string targ, unsigned col) {
    double compteur = 0;
    double nbStr = 0;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        if(m_mat[i][col] == str) {
            nbStr = nbStr + 1;
            if(m_mat[i][3] == targ) {
                compteur = compteur + 1;
            }
        }
    }
    return compteur/nbStr;
}
