#include "game.h"
#include "ui_game.h"
#include "artificialintelligence.h"
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    img3.load("/home/ania/projekty/RockPaperScissor/Images/3.png");
    img2.load("/home/ania/projekty/RockPaperScissor/Images/2.png");
    img1.load("/home/ania/projekty/RockPaperScissor/Images/1.png");

    rock.load("/home/ania/projekty/RockPaperScissor/Images/rock.png");
    paper.load("/home/ania/projekty/RockPaperScissor/Images/paper.png");
    scissors.load("/home/ania/projekty/RockPaperScissor/Images/scissors.png");

    counter = 0;
    size = 5;
    computer_score = 0;
    player_score = 0;
    com_sign = 0;
    AI = new ArtificialIntelligence();
    gThread = new GameThread(this);
    connect(gThread, SIGNAL(FieldChanged(int)), this, SLOT(onFieldChanged(int)));
}

Game::~Game()
{
    delete ui;
}

void Game::onFieldChanged(int Number)
{
    QGraphicsScene* scene = new QGraphicsScene;
    ui->computer->setScene(scene);
    scene->setBackgroundBrush(Qt::black);

    QImage img;
    if(Number == 0)
    {
        img = img3;
        ui->result->setText("");
    }
    else if(Number == 1) img = img2;
    else if(Number == 2) img = img1;
    else
    {
        int num = checkPlayer();
        img = chooseSign(num);
        updateScore(num);
        updateResult(num);
    }

    scene->addPixmap(QPixmap::fromImage(img));

    ui->computer->show();

    ui->score_computer->setText(QString::number(computer_score));
    ui->score_player->setText(QString::number(player_score));
}

void Game::on_Start_clicked()
{
    gThread->Stop = false;
    gThread->start();
}

void Game::on_Stop_clicked()
{
    gThread->Stop = true;
}

QImage Game::chooseSign(int player_sign)
{
    QImage img;
    com_sign = AI->play(player_sign);
    if(com_sign == 1) img = rock;
    else if(com_sign == 2) img = paper;
    else img = scissors;

    return img;
}

void Game::updatePlayer(QImage img)
{
    QGraphicsScene* scene = new QGraphicsScene;
    ui->player->setScene(scene);
    scene->setBackgroundBrush(Qt::black);
    scene->addPixmap(QPixmap::fromImage(img));

    ui->player->show();
}

void Game::updateResult(int Number)
{
    if(Number == 2) ui->result->setText("Papier");
    else if (Number == 3) ui->result->setText("Nożyczki");
    else if (Number == 1) ui->result->setText("Kamień");
    else ui->result->setText("Nie wykryto");
}

void Game::updateList(int i)
{
    list[counter] = i;
    counter = (counter + 1) % size;
}

int Game::checkPlayer()
{
    int c_paper = 0, c_scissors = 0, c_rock = 0, c_empty = 0;
    for(int i= 0; i< size; i++)
    {
        if (list[i] == 1) c_rock++;
        else if (list[i] == 2) c_paper++;
        else if (list[i] == 3) c_scissors++;
        else c_empty++;
    }
    int temp = max_c(c_paper, c_rock, c_scissors, c_empty);
    if(temp == c_rock) return 1;
    if(temp == c_paper) return 2;
    if(temp == c_scissors) return 3;
    return 0;
}

int Game::max_c(int a, int b, int c, int d)
{
    bool max_a = false, max_c = false;
    if(a > b) max_a = true;
    if(c > d) max_c = true;
    if(max_a)
    {
        if(max_c)
        {
            if(a > c) return a;
            else return c;
        }
        else
        {
            if(a > d) return a;
            else return d;
        }
    }
    else
    {
        if(max_c)
        {
            if(b > c) return b;
            else return c;
        }
        else
        {
            if(b > d) return b;
            else return d;
        }
    }
}

void Game::updateScore(int my_sign)
{
    if(com_sign == 1) //Kamień
    {
        if(my_sign == 2)  player_score++;//Papier
        else if(my_sign == 3) computer_score++; //Nożyczki
    }
    else if(com_sign == 2) //Papier
    {
        if(my_sign == 1) computer_score++; //Kamień
        else if(my_sign == 3) player_score++; //Nożyczki
    }
    else if(com_sign == 3) //Nożyczki
    {
        if(my_sign == 2) computer_score++; //Papier
        else if(my_sign == 1) player_score++; //Kamień
    }
}
