#include "systemcenter.h"
#include "ui_systemcenter.h"
#include "QElapsedTimer"
#include <QHeaderView>
#include <QMovie>
#include <QIntValidator>
#include <QListView>

/**
 * SystemCenter UI initialize
 *
 * @author hzc
 */
SystemCenter::SystemCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemCenter)
{
    ui->setupUi(this);

    m_tcpsocket = new QTcpSocket;
    m_tcpsocket->connectToHost(QHostAddress::LocalHost,8848);//设置客户端的端口号
    connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage()));//用于接受数据
			
	m_socket = new QTcpSocket;
    m_socket->connectToHost(QHostAddress::LocalHost, 7777);
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(replyFinished()));

    ui->label_navigator->setVisible(false);


    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("QFrame{border-radius:10px;}");

    /*
     * Add anything here to function 'showString' in this page
     *
     * for slow start
     *
     */
}

/**
 * SystemCenter UI destory
 *
 * @author hzc
 */
SystemCenter::~SystemCenter()
{
    delete ui;
    qDebug() << "Destory : systemcenter" << endl;
}

/**
 * on_pushButton_clicked
 *
 * @author hzc
 */
void SystemCenter::on_pushButton_quit_clicked()
{
    this->close();
}

/**
 * slot method
 *
 * @author hzc
 * @param s1 username
 * @param s2 name
 * @param s3 position
 * @param s4 gender
 * @param s5 email
 */
void SystemCenter::showString(QString s1, QString s2, QString s3, QString s4, QString s5, QString s6)
{
    this->show();
    ui->pushButton_switch->setEnabled(false);

    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_tabBarClicked(0);

    if(s3 == "管理员"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(2);
        ui->tabWidget->removeTab(3);
        ui->tabWidget->removeTab(4);
    }
    if(s3 == "采购人员"){
        ui->tabWidget->removeTab(2);
        ui->tabWidget->removeTab(3);
        ui->tabWidget->removeTab(4);
        ui->tabWidget->removeTab(6);
    }

    if(s3 == "物流管理"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(3);
        ui->tabWidget->removeTab(4);
        ui->tabWidget->removeTab(6);

    }

    if(s3 == "仓库管理"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(2);
        ui->tabWidget->removeTab(4);
        ui->tabWidget->removeTab(6);

    }

    if(s3 == "销售管理"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(2);
        ui->tabWidget->removeTab(3);
        ui->tabWidget->removeTab(6);

    }

    /*
     * slow start
     *
     */

    ui->label_showEditPortrait->installEventFilter(this);
    ui->label_showEditPortrait->setAcceptDrops(true);

    ui->label_showNewPortrait->installEventFilter(this);
    ui->label_showNewPortrait->setAcceptDrops(true);

    ui->label_showGPic->installEventFilter(this);
    ui->label_showGPic->setAcceptDrops(true);

    ui->label_2->setText(s1);
    ui->label_4->setText(s2);
    ui->label_8->setText(s3);
    ui->label_12->setText(s4);
    ui->label_14->setText(s5);

    ui->pushButton_57->setStyleSheet("QPushButton{border: 2px solid  rgb(15, 128, 255);"
                                     "background:rgba(15, 128, 255, 43);"
                                     "border-radius:29px;"
                                     "color: rgb(76, 76, 76);"
                                     "font: 75 15pt \"Helvetica\" bold;}");
    ui->progressBar->setVisible(false);
    ui->pushButton_17->setVisible(false);
    ui->pushButton_18->setVisible(false);
    ui->add_warehouse->setVisible(false);
    ui->edit_warehouse->setVisible(false);
    ui->label_showEditPortraitPath->setVisible(false);
    ui->comboBox_addNewGender->setView(new QListView());
    ui->comboBox_addNewPosition->setView(new QListView());
    ui->comboBox_updateStaffGender->setView(new QListView());
    ui->comboBox_updateStaffPosition->setView(new QListView());


    ui->comboBox_sellDUserName->setView(new QListView());
    ui->comboBox_2->setView(new QListView());
    QApplication::processEvents();


    QPixmap *pixmap = new QPixmap(DIR + QString("/users/") + s6);
    if (pixmap->isNull()){
        download("/users/" + s6, DIR + QString("/users/") + s6);
    }

    if(pixmap->isNull()){
        pixmap = new QPixmap(":/user.png");
    }

    QApplication::processEvents();

    getRoundPixmap(pixmap, QSize(140, 140));
    ui->label_5->setScaledContents(true);
    ui->label_5->setPixmap(*pixmap);
    delete pixmap;

    QApplication::processEvents();


    int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    //initialize tiny icon

    QFont font;
    font.setFamily(fontFamilies.at(0));
    font.setPointSize(15);
    ui->label->setFont(font);
    ui->label->setText(QChar(0xf007));
    ui->label->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");
    ui->label_9->setFont(font);
    ui->label_9->setText(QChar(0xf530));
    ui->label_9->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");
    ui->label_10->setFont(font);
    ui->label_10->setText(QChar(0xf182));
    ui->label_10->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");
    ui->label_13->setFont(font);
    ui->label_13->setText(QChar(0xf2b6));
    ui->label_13->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QApplication::processEvents();
    ui->label_23->setFont(font);
    ui->label_23->setText(QChar(0xf551));
    ui->label_23->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_24->setFont(font);
    ui->label_24->setText(QChar(0xf4d9));
    ui->label_24->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_25->setFont(font);
    ui->label_25->setText(QChar(0xf2f2));
    ui->label_25->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_42->setFont(font);
    ui->label_42->setText(QChar(0xf02d));
    ui->label_42->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QApplication::processEvents();

    ui->label_43->setFont(font);
    ui->label_43->setText(QChar(0xf471));
    ui->label_43->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_44->setFont(font);
    ui->label_44->setText(QChar(0xf155));
    ui->label_44->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_46->setFont(font);
    ui->label_46->setText(QChar(0xf022));
    ui->label_46->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_37->setFont(font);
    ui->label_37->setText(QChar(0xf0d1));
    ui->label_37->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QApplication::processEvents();

    ui->label_41->setFont(font);
    ui->label_41->setText(QChar(0xf5cb));
    ui->label_41->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_66->setFont(font);
    ui->label_66->setText(QChar(0xf02d));
    ui->label_66->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QApplication::processEvents();

    ui->label_67->setFont(font);
    ui->label_67->setText(QChar(0xf471));
    ui->label_67->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_68->setFont(font);
    ui->label_68->setText(QChar(0xf155));
    ui->label_68->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_70->setFont(font);
    ui->label_70->setText(QChar(0xf022));
    ui->label_70->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_77->setFont(font);
    ui->label_77->setText(QChar(0xf4de));
    ui->label_77->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_102->setFont(font);
    ui->label_102->setText(QChar(0xf1de));
    ui->label_102->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_104->setFont(font);
    ui->label_104->setText(QChar(0xf55f));
    ui->label_104->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_107->setFont(font);
    ui->label_107->setText(QChar(0xf56e));
    ui->label_107->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_storeN->setFont(font);
    ui->label_font_storeN->setText(QChar(0xf54e));
    ui->label_font_storeN->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_manager->setFont(font);
    ui->label_font_manager->setText(QChar(0xf222));
    ui->label_font_manager->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_location->setFont(font);
    ui->label_font_location->setText(QChar(0xf124));
    ui->label_font_location->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_storeN_C->setFont(font);
    ui->label_font_storeN_C->setText(QChar(0xf54e));
    ui->label_font_storeN_C->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_manager_C->setFont(font);
    ui->label_font_manager_C->setText(QChar(0xf222));
    ui->label_font_manager_C->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_location_C->setFont(font);
    ui->label_font_location_C->setText(QChar(0xf124));
    ui->label_font_location_C->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_85->setFont(font);
    ui->label_85->setText(QChar(0xf1b3));
    ui->label_85->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_110->setFont(font);
    ui->label_110->setText(QChar(0xf560));
    ui->label_110->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_191->setFont(font);
    ui->label_191->setText(QChar(0xf52d));
    ui->label_191->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_194->setFont(font);
    ui->label_194->setText(QChar(0xf474));
    ui->label_194->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_196->setFont(font);
    ui->label_196->setText(QChar(0xf1b3));
    ui->label_196->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_198->setFont(font);
    ui->label_198->setText(QChar(0xf59d));
    ui->label_198->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_124->setFont(font);
    ui->label_124->setText(QChar(0xf058));
    ui->label_124->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_125->setFont(font);
    ui->label_125->setText(QChar(0xf017));
    ui->label_125->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_126->setFont(font);
    ui->label_126->setText(QChar(0xf461));
    ui->label_126->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_202->setFont(font);
    ui->label_202->setText(QChar(0xf2d2));
    ui->label_202->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_201->setFont(font);
    ui->label_201->setText(QChar(0xf54e));
    ui->label_201->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_204->setFont(font);
    ui->label_204->setText(QChar(0xf0a4));
    ui->label_204->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_309->setFont(font);
    ui->label_309->setText(QChar(0xf0e3));
    ui->label_309->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_311->setFont(font);
    ui->label_311->setText(QChar(0xf017));
    ui->label_311->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_79->setFont(font);
    ui->label_79->setText(QChar(0xf02d));
    ui->label_79->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QApplication::processEvents();

    ui->label_88->setFont(font);
    ui->label_88->setText(QChar(0xf471));
    ui->label_88->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_89->setFont(font);
    ui->label_89->setText(QChar(0xf155));
    ui->label_89->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_91->setFont(font);
    ui->label_91->setText(QChar(0xf022));
    ui->label_91->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_312->setFont(font);
    ui->label_312->setText(QChar(0xf017));
    ui->label_312->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_130->setFont(font);
    ui->label_130->setText(QChar(0xf02d));
    ui->label_130->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QApplication::processEvents();

    ui->label_131->setFont(font);
    ui->label_131->setText(QChar(0xf471));
    ui->label_131->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_132->setFont(font);
    ui->label_132->setText(QChar(0xf155));
    ui->label_132->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_133->setFont(font);
    ui->label_133->setText(QChar(0xf022));
    ui->label_133->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_143->setFont(font);
    ui->label_143->setText(QChar(0xf2b6));
    ui->label_143->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_141->setFont(font);
    ui->label_141->setText(QChar(0xf5ab));
    ui->label_141->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_142->setFont(font);
    ui->label_142->setText(QChar(0xf4cd));
    ui->label_142->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_140->setFont(font);
    ui->label_140->setText(QChar(0xf0c7));
    ui->label_140->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_134->setFont(font);
    ui->label_134->setText(QChar(0xf3e0));
    ui->label_134->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_135->setFont(font);
    ui->label_135->setText(QChar(0xf0fe));
    ui->label_135->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_136->setFont(font);
    ui->label_136->setText(QChar(0xf183));
    ui->label_136->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_137->setFont(font);
    ui->label_137->setText(QChar(0xf593));
    ui->label_137->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_139->setFont(font);
    ui->label_139->setText(QChar(0xf2b6));
    ui->label_139->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");


    ui->label_144->setFont(font);
    ui->label_144->setText(QChar(0xf05a));
    ui->label_144->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_145->setFont(font);
    ui->label_145->setText(QChar(0xf53c));
    ui->label_145->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_146->setFont(font);
    ui->label_146->setText(QChar(0xf248));
    ui->label_146->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_147->setFont(font);
    ui->label_147->setText(QChar(0xf599));
    ui->label_147->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_148->setFont(font);
    ui->label_148->setText(QChar(0xf182));
    ui->label_148->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_149->setFont(font);
    ui->label_149->setText(QChar(0xf0e0));
    ui->label_149->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_150->setFont(font);
    ui->label_150->setText(QChar(0xf362));
    ui->label_150->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_155->setFont(font);
    ui->label_155->setText(QChar(0xf192));
    ui->label_155->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_156->setFont(font);
    ui->label_156->setText(QChar(0xf4ba));
    ui->label_156->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_157->setFont(font);
    ui->label_157->setText(QChar(0xf56a));
    ui->label_157->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_151->setFont(font);
    ui->label_151->setText(QChar(0xf1b2));
    ui->label_151->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_152->setFont(font);
    ui->label_152->setText(QChar(0xf563));
    ui->label_152->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_153->setFont(font);
    ui->label_153->setText(QChar(0xf520));
    ui->label_153->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_154->setFont(font);
    ui->label_154->setText(QChar(0xf51e));
    ui->label_154->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_159->setFont(font);
    ui->label_159->setText(QChar(0xf522));
    ui->label_159->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_160->setFont(font);
    ui->label_160->setText(QChar(0xf254));
    ui->label_160->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_162->setFont(font);
    ui->label_162->setText(QChar(0xf3d1));
    ui->label_162->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_164->setFont(font);
    ui->label_164->setText(QChar(0xf058));
    ui->label_164->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_165->setFont(font);
    ui->label_165->setText(QChar(0xf277));
    ui->label_165->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");





    QFont sp_font;
    sp_font.setFamily(fontFamilies.at(0));
    sp_font.setPointSize(18);

    ui->pushButton_font_sellSearch->setFont(sp_font);
    ui->pushButton_font_sellSearch->setText(QChar(0xf0d0));
    ui->pushButton_font_sellSearch->setStyleSheet("QPushButton{border: 0px; color: rgb(127, 127, 127);} "
                                                  "QPushButton:hover{border: 0px; color: rgb(15, 128, 255);} ");

    ui->label_navigator->setFont(sp_font);
    ui->label_navigator->setText(QChar(0xf5a0));
    ui->label_navigator->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    QFont sp_font2;
    sp_font2.setFamily(fontFamilies.at(0));
    sp_font2.setPointSize(90);

    //initialize search icon

    QFont icon_search;
    icon_search.setFamily(fontFamilies.at(0));
    icon_search.setPointSize(24);
    ui->icon_search->setFont(icon_search);
    ui->icon_search->setText(QChar(0xf35a));
    ui->icon_search->setStyleSheet("QPushButton{border: 0px; color: rgb(127, 127, 127);} "
                                   "QPushButton:hover{border: 0px; color: rgb(15, 128, 255);} ");

    ui->icon_search_B->setFont(icon_search);
    ui->icon_search_B->setText(QChar(0xf35a));
    ui->icon_search_B->setStyleSheet("QPushButton{border: 0px; color: rgb(127, 127, 127);} "

                                     "QPushButton:hover{border: 0px; color: rgb(15, 128, 255);} ");

    ui->icon_search_C->setFont(icon_search);
    ui->icon_search_C->setText(QChar(0xf35a));
    ui->icon_search_C->setStyleSheet("QPushButton{border: 0px; color: rgb(127, 127, 127);} "
                                     "QPushButton:hover{border: 0px; color: rgb(15, 128, 255);} ");


    ui->icon_search_D->setFont(icon_search);
    ui->icon_search_D->setText(QChar(0xf35a));
    ui->icon_search_D->setStyleSheet("QPushButton{border: 0px; color: rgb(127, 127, 127);} "
                                     "QPushButton:hover{border: 0px; color: rgb(15, 128, 255);} ");

    ui->pushButton_font_sellSearch_2->setFont(icon_search);
    ui->pushButton_font_sellSearch_2->setText(QChar(0xf35a));
    ui->pushButton_font_sellSearch_2->setStyleSheet("QPushButton{border: 0px; color: rgb(127, 127, 127);} "
                                     "QPushButton:hover{border: 0px; color: rgb(15, 128, 255);} ");

    ui->style_change->setFont(icon_search);
    ui->style_change->setText(QChar(0xf204));
    ui->style_change->setStyleSheet("QPushButton{border: 0px; color: white;} "
                                    "QPushButton:hover{border: 0px; color: rgba(15, 128, 255, 190);} ");

    //frame_sell_D
    ui->label_font_sellD1Name->setFont(font);
    ui->label_font_sellD1Name->setText(QChar(0xf1ad));
    ui->label_font_sellD1Name->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD1Province->setFont(font);
    ui->label_font_sellD1Province->setText(QChar(0xf19c));
    ui->label_font_sellD1Province->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD1City->setFont(font);
    ui->label_font_sellD1City->setText(QChar(0xf015));
    ui->label_font_sellD1City->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD1Address->setFont(font);
    ui->label_font_sellD1Address->setText(QChar(0xf124));
    ui->label_font_sellD1Address->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD1Administrator->setFont(font);
    ui->label_font_sellD1Administrator->setText(QChar(0xf4fe));
    ui->label_font_sellD1Administrator->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD2Name->setFont(font);
    ui->label_font_sellD2Name->setText(QChar(0xf1ad));
    ui->label_font_sellD2Name->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD2Province->setFont(font);
    ui->label_font_sellD2Province->setText(QChar(0xf19c));
    ui->label_font_sellD2Province->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD2City->setFont(font);
    ui->label_font_sellD2City->setText(QChar(0xf015));
    ui->label_font_sellD2City->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD2Address->setFont(font);
    ui->label_font_sellD2Address->setText(QChar(0xf124));
    ui->label_font_sellD2Address->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellD2Administrator->setFont(font);
    ui->label_font_sellD2Administrator->setText(QChar(0xf4fe));
    ui->label_font_sellD2Administrator->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellDCloth->setFont(font);
    ui->label_font_sellDCloth->setText(QChar(0xf553));
    ui->label_font_sellDCloth->setStyleSheet("border: 0px; color: rgb(106, 106, 106);background:none;");

    ui->label_font_sellDCloth->setVisible(false);

    QFont icon_direction;
    icon_direction.setFamily(fontFamilies.at(0));
    icon_direction.setPointSize(20);
    ui->pushButton_sell_right->setFont(icon_direction);
    ui->pushButton_sell_right->setText(QChar(0xf0a4));
    ui->pushButton_sell_left->setFont(icon_direction);
    ui->pushButton_sell_left->setText(QChar(0xf0a5));

    QApplication::processEvents();

    //set size of tablewidget

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(105);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setAlternatingRowColors(true);

    ui->tableWidget_A->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidget_A->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_A->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_A->setAlternatingRowColors(true);

    ui->tableWidget_B->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_B->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_B->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget_B->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_B->setAlternatingRowColors(true);

    ui->tableWidget_B_2->horizontalHeader()->setDefaultSectionSize(93);
    ui->tableWidget_B_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_B_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_B_2->setAlternatingRowColors(true);

    ui->tableWidget_C1->horizontalHeader()->setDefaultSectionSize(93);
    ui->tableWidget_C1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_C1->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    ui->tableWidget_C1->setAlternatingRowColors(true);

    ui->tableWidget_C2->horizontalHeader()->setDefaultSectionSize(93);
    ui->tableWidget_C2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_C2->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    ui->tableWidget_C2->setAlternatingRowColors(true);

    ui->tableWidget_D1->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_D1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_D1->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget_D1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_D1->setAlternatingRowColors(true);

    ui->tableWidget_D2->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_D2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_D2->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget_D2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_D2->setAlternatingRowColors(true);

    ui->tableWidget_D3->horizontalHeader()->setDefaultSectionSize(93);
    ui->tableWidget_D3->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_D3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_D3->setAlternatingRowColors(true);

    ui->tableWidget_D4->horizontalHeader()->setDefaultSectionSize(10);
    ui->tableWidget_D4->setColumnWidth(0,73);
    ui->tableWidget_D4->setColumnWidth(1,130);
    ui->tableWidget_D4->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_D4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_D4->setAlternatingRowColors(true);


    ui->tableWidget_stores->horizontalHeader()->setDefaultSectionSize(90);
    ui->tableWidget_stores->setColumnWidth(0,40);
    ui->tableWidget_stores->setColumnWidth(4,220);
    ui->tableWidget_stores->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_stores->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_stores->setAlternatingRowColors(true);

    ui->tableWidget_logistics_A->horizontalHeader()->setDefaultSectionSize(120);
    ui->tableWidget_logistics_A->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_A->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_A->setAlternatingRowColors(true);

    ui->tableWidget_logistics_B->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_logistics_B->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_B->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget_logistics_B->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_B->setAlternatingRowColors(true);

    ui->tableWidget_logistics_C->horizontalHeader()->setDefaultSectionSize(85);
    ui->tableWidget_logistics_C->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_C->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_C->setAlternatingRowColors(true);

    ui->tableWidget_logistics_D->setColumnWidth(1, 70);
    ui->tableWidget_logistics_D->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_D->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_D->setAlternatingRowColors(true);

    ui->tableWidget_logistics_2A->horizontalHeader()->setDefaultSectionSize(120);
    ui->tableWidget_logistics_2A->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_2A->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_2A->setAlternatingRowColors(true);

    ui->tableWidget_logistics_C1->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_logistics_C1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_C1->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget_logistics_C1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_C1->setAlternatingRowColors(true);

    ui->tableWidget_logistics_C2->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_logistics_C2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_C2->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget_logistics_C2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_C2->setAlternatingRowColors(true);

    ui->tableWidget_route_via->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_route_via->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_route_via->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_route_via->setAlternatingRowColors(true);


    ui->tableWidget_generateOrder->horizontalHeader()->setDefaultSectionSize(95);
    ui->tableWidget_generateOrder->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_generateOrder->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_generateOrder->setAlternatingRowColors(true);

    ui->tableWidget_orderGarment->horizontalHeader()->setDefaultSectionSize(115);
    ui->tableWidget_orderGarment->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_orderGarment->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_orderGarment->setAlternatingRowColors(true);

    ui->tableWidget_deliverGarment->horizontalHeader()->setDefaultSectionSize(115);
    ui->tableWidget_deliverGarment->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_deliverGarment->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_deliverGarment->setAlternatingRowColors(true);
    ui->tableWidget_deliverGarment->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->tableWidget_deliverProvider->horizontalHeader()->setDefaultSectionSize(115);
    ui->tableWidget_deliverProvider->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_deliverProvider->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_deliverProvider->setAlternatingRowColors(true);

    ui->tableWidget_showStaffInfo->horizontalHeader()->setDefaultSectionSize(105);
    ui->tableWidget_showStaffInfo->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_showStaffInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_showStaffInfo->setAlternatingRowColors(true);

    ui->tw_sellD1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_sellD1->setAlternatingRowColors(true);

    ui->tw_sellD2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_sellD2->setAlternatingRowColors(true);

    ui->tw_sellD3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_sellD3->setAlternatingRowColors(true);

    ui->tw_sell_C2->setColumnWidth(0, 40);
    ui->tw_sell_C2->setColumnWidth(1, 200);
    ui->tw_sell_C2->horizontalHeader()->setStretchLastSection(true);
    ui->tw_sell_C2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_sell_C2->setAlternatingRowColors(true);

    ui->tableWidget_check->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_check->setAlternatingRowColors(true);

    ui->tableWidget_checkDetail->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_checkDetail->setAlternatingRowColors(true);

    ui->tw_sell_C1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_sell_C1->setAlternatingRowColors(true);

    ui->tableWidget_stores->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_stores->setAlternatingRowColors(true);

    ui->tableWidget_updateShowStaffInfo->horizontalHeader()->setDefaultSectionSize(105);
    ui->tableWidget_updateShowStaffInfo->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_updateShowStaffInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_updateShowStaffInfo->setAlternatingRowColors(true);

    ui->tableWidget_providerInfo->horizontalHeader()->setDefaultSectionSize(130);
    ui->tableWidget_providerInfo->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_providerInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_providerInfo->setAlternatingRowColors(true);
    ui->label_showPicPath->setVisible(false);

    ui->tableWidget_garmentInfo->horizontalHeader()->setDefaultSectionSize(120);
    ui->tableWidget_garmentInfo->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_garmentInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_garmentInfo->setAlternatingRowColors(true);

    ui->tableWidget_logistics_D1->horizontalHeader()->setDefaultSectionSize(120);
    ui->tableWidget_logistics_D1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_D1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_D1->setAlternatingRowColors(true);

    ui->tableWidget_logistics_D4->setColumnWidth(1, 70);
    ui->tableWidget_logistics_D4->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_D4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_D4->setAlternatingRowColors(true);

    ui->tableWidget_logistics_D2->horizontalHeader()->setDefaultSectionSize(90);
    ui->tableWidget_logistics_D2->setColumnWidth(3, 100);
    ui->tableWidget_logistics_D2->setColumnWidth(4, 85);
    ui->tableWidget_logistics_D2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_logistics_D2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_logistics_D2->setAlternatingRowColors(true);



    style = false;
    QFile *file = new QFile(CONFIG_DIR);
    if(file->exists()){
        if (file->open(QFile::ReadWrite | QFile::Text)){
           QString status;
           status = file->readLine().trimmed();
           if(status == "1"){
               style = !style;
               int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf");
               QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
               QFont icon_search;
               icon_search.setFamily(fontFamilies.at(0));
               icon_search.setPointSize(24);
               ui->frame->setStyleSheet("QFrame{background: rgba(255, 255, 255, 0);"
                                        "border-image:url(:/bg5.png);}");
               ui->style_change->setFont(icon_search);
               ui->style_change->setText(QChar(0xf205));
               ui->style_change->setStyleSheet("QPushButton{border: 0px; color: white;} "
                                               "QPushButton:hover{border: 0px; color: rgba(15, 128, 255, 190);} ");
           }
        }else{
            qDebug()<<"打开失败";
        }
    }
    file->close();





    QApplication::processEvents();
    //fuzzy search

    connect(ui->warehouse_search_A, SIGNAL(returnPressed()), ui->icon_search, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->warehouse_search_B, SIGNAL(returnPressed()), ui->icon_search_B, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->warehouse_search_C, SIGNAL(returnPressed()), ui->icon_search_C, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->warehouse_search_D, SIGNAL(returnPressed()), ui->icon_search_D, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->quantity_D, SIGNAL(returnPressed()), ui->clothes_ADD, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->warehouse_id, SIGNAL(returnPressed()), ui->w_search_A, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->quantity_logistics, SIGNAL(returnPressed()), ui->logistics_ADD, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->lineEdit_garmentNum, SIGNAL(returnPressed()), ui->pushButton_addGarment, SIGNAL(clicked()), Qt::UniqueConnection);

    connect(ui->lineEdit_searchStaffValue, SIGNAL(returnPressed()), ui->pushButton_font_sellSearch_2, SIGNAL(clicked()), Qt::UniqueConnection);


    QApplication::processEvents();

    ui->stackedWidget_sellD->setCurrentIndex(0);
    ui->label_sellDStoreId->setVisible(false);
    ui->label_sell_row->setVisible(false);
    ui->label_sell_idPurchase->setVisible(false);
    ui->pushButton_change->setVisible(false);
    ui->pushButton_commit->setVisible(false);
    ui->pushButton_reject->setVisible(false);
    ui->tw_sellD3->verticalHeader()->setVisible(false);

    QIntValidator *validator = new QIntValidator(1, 2000, this);
    ui->lineEdit_sellDAmount->setValidator(validator);
    ui->lineEdit_sell_amount->setValidator(validator);

    /**
     * purchase page date/time label display
     *
     * @author Yihan Dong
     */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_deal_slot_function()));
    timer->start(1000);


    /**
     * Add new staff page setting
     *
     * @author Yihan Dong
    */

    ui->label_newStaffUsernameTip->setVisible(false);
    ui->label_newStaffEmailTip->setVisible(false);
    ui->label_repeatPasswordTip->setVisible(false);
    ui->label_showNewPortraitPath->setVisible(false);
    ui->lineEdit_addNewPassword->setEchoMode(QLineEdit::Password);
    ui->lineEdit_repeatPassword->setEchoMode(QLineEdit::Password);


    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(10);


    ui->label_updateEmailTip->setVisible(false);
    ui->label_updatePasswordTip->setVisible(false);


    //initialize furry search

    QElapsedTimer t;

    warehouseEditComplete();
    m_tcpsocket->flush();

    ui->progressBar->setValue(20);


    t.start();
    while(t.elapsed()<1000)
        QCoreApplication::processEvents();

    ui->progressBar->setValue(35);

    //initialize arriving table
    transfer();
    m_tcpsocket->flush();

    ui->progressBar->setValue(50);

    //    QMovie *movie = new QMovie(":/movie.gif");
    //    ui->label_title->setMovie(movie);
    //    movie->start();

}




/**
 * shape picture to circle
 *
 * @author hzc
 * @param s1 username
 * @param s2 name
 * @param s3 position
 * @param s4 gender
 * @param s5 email
 */
void SystemCenter::getRoundPixmap(QPixmap* src,QSize size)

{

    QImage resultImage(size,QImage::Format_ARGB32_Premultiplied);
    QPixmap head_mask(":/mask.png");
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, head_mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
    painter.drawPixmap(0, 0, src->scaled(size));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.end();
    *src = QPixmap::fromImage(resultImage);
}

/**
 * slot method
 *
 * @author hzc
 * @param index tab index of tab widget
 */
void SystemCenter::on_tabWidget_tabBarClicked(int index){
    on_pushButton_A_clicked();
    if(index == 0){
        ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        ui->pushButton_A->setText("");
        ui->pushButton_B->setText("");
        ui->pushButton_C->setText("");
        ui->pushButton_D->setText("");

    }
    if(index == 1){
         ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        ui->pushButton_A->setText("Generate");
        ui->pushButton_B->setText("Delivery");
        ui->pushButton_C->setText("");
        ui->pushButton_D->setText("");

    }
    if(index == 2){
        ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        ui->pushButton_A->setText("Replenish");
        ui->pushButton_B->setText("History");
        ui->pushButton_C->setText("Route");
        ui->pushButton_D->setText("Auto");

    }
    if(index == 3){
        ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        ui->pushButton_A->setText("Info");
        ui->pushButton_B->setText("Cargo");
        ui->pushButton_C->setText("Inventory");
        ui->pushButton_D->setText("Demand");
    }
    if(index == 4){
        ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        ui->pushButton_A->setText("Record");
        ui->pushButton_B->setText("Delivery");
        ui->pushButton_C->setText("Arrive");
        ui->pushButton_D->setText("Manage");

    }
    if(index == 5){
        ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        if(ui->label_8->text() == "管理员" ||
                ui->label_8->text() == "测试用"){
            ui->pushButton_A->setText("Display");
            ui->pushButton_B->setText("Add");
            ui->pushButton_C->setText("Modify");
            ui->pushButton_D->setText("Security");
        }else{
             ui->pushButton_A->setText("Security");
             ui->pushButton_B->setText("");
             ui->pushButton_C->setText("");
             ui->pushButton_D->setText("");
        }



    }
    if(index == 6){
         ui->pushButton_A->setVisible(true);
        ui->pushButton_B->setVisible(true);
        ui->pushButton_C->setVisible(true);
        ui->pushButton_D->setVisible(true);

        ui->pushButton_A->setText("Garment");
        ui->pushButton_B->setText("Manage");
        ui->pushButton_C->setText("Addition");
        ui->pushButton_D->setText("");

    }
}

/**
 * on_pushButton_A_clicked slot
 *
 * @author hzc
 */
void SystemCenter::on_pushButton_A_clicked()
{
    ui->pushButton_A->setChecked(true);

    //A
    ui->frame_2A->setVisible(true);
    ui->frame_pA->setVisible(true);
    ui->frame_systempage_1->setVisible(true);
    ui->frame_sell_A->setVisible(true);
    ui->frame_logistics_A->setVisible(true);


    //B
    ui->frame_2B->setVisible(false);
    ui->frame_pB->setVisible(false);
    ui->frame_systempage_2->setVisible(false);
    ui->frame_sell_B->setVisible(false);
    ui->frame_logistics_B->setVisible(false);

    //C
    ui->frame_2C->setVisible(false);
    ui->frame_sell_C->setVisible(false);
    ui->frame_logistics_C->setVisible(false);
    ui->frame_systempage_3->setVisible(false);

    //D
    ui->frame_2D->setVisible(false);
    ui->frame_sell_D->setVisible(false);
    ui->frame_logistics_D->setVisible(false);

    if(ui->label_8->text() == "管理员" ||
            ui->label_8->text() == "测试用"){
        ui->frame_personnelpage_1->setVisible(true);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(false);
    }else{
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(true);
    }

}

/**
 * on_pushButton_B_clicked slot
 *
 * @author hzc
 */
void SystemCenter::on_pushButton_B_clicked()
{
    //A
    ui->frame_2A->setVisible(false);
    ui->frame_pA->setVisible(false);
    ui->frame_systempage_1->setVisible(false);
    ui->frame_sell_A->setVisible(false);
    ui->frame_logistics_A->setVisible(false);

    //B
    ui->frame_2B->setVisible(true);
    ui->frame_pB->setVisible(true);
    ui->frame_systempage_2->setVisible(true);
    ui->frame_sell_B->setVisible(true);
    ui->frame_logistics_B->setVisible(true);

    //C
    ui->frame_2C->setVisible(false);
    ui->frame_sell_C->setVisible(false);
    ui->frame_logistics_C->setVisible(false);
    ui->frame_systempage_3->setVisible(false);

    //D
    ui->frame_2D->setVisible(false);
    ui->frame_sell_D->setVisible(false);
    ui->frame_logistics_D->setVisible(false);

    if(ui->label_8->text() == "管理员" ||
            ui->label_8->text() == "测试用"){
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(true);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(false);
    }else{
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(true);
    }
}

/**
 * on_pushButton_C_clicked slot
 *
 * @author hzc
 */
void SystemCenter::on_pushButton_C_clicked()
{
    //A
    ui->frame_2A->setVisible(false);
    ui->frame_pA->setVisible(false);
    ui->frame_systempage_1->setVisible(false);
    ui->frame_sell_A->setVisible(false);
    ui->frame_logistics_A->setVisible(false);

    //B
    ui->frame_2B->setVisible(false);
    ui->frame_pB->setVisible(false);
    ui->frame_systempage_2->setVisible(false);
    ui->frame_sell_B->setVisible(false);
    ui->frame_logistics_B->setVisible(false);

    //C
    ui->frame_2C->setVisible(true);
    ui->frame_sell_C->setVisible(true);
    ui->frame_logistics_C->setVisible(true);
    ui->frame_systempage_3->setVisible(true);

    //D
    ui->frame_2D->setVisible(false);
    ui->frame_sell_D->setVisible(false);
    ui->frame_logistics_D->setVisible(false);

    if(ui->label_8->text() == "管理员" ||
            ui->label_8->text() == "测试用"){
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(true);
        ui->frame_personnelpage_4->setVisible(false);
    }else{
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(true);
    }

}

/**
 * on_pushButton_D_clicked slot
 *
 * @author hzc
 */
void SystemCenter::on_pushButton_D_clicked()
{
    //A
    ui->frame_2A->setVisible(false);
    ui->frame_pA->setVisible(false);
    ui->frame_systempage_1->setVisible(false);
    ui->frame_sell_A->setVisible(false);
    ui->frame_logistics_A->setVisible(false);

    //B
    ui->frame_2B->setVisible(false);
    ui->frame_pB->setVisible(false);
    ui->frame_systempage_2->setVisible(false);
    ui->frame_sell_B->setVisible(false);
    ui->frame_logistics_B->setVisible(false);

    //C
    ui->frame_2C->setVisible(false);
    ui->frame_sell_C->setVisible(false);
    ui->frame_logistics_C->setVisible(false);
    ui->frame_systempage_3->setVisible(false);

    //D
    ui->frame_2D->setVisible(true);
    ui->frame_sell_D->setVisible(true);
    ui->frame_logistics_D->setVisible(true);

    if(ui->label_8->text() == "管理员" ||
            ui->label_8->text() == "测试用"){
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(true);
    }else{
        ui->frame_personnelpage_1->setVisible(false);
        ui->frame_personnelpage_2->setVisible(false);
        ui->frame_personnelpage_3->setVisible(false);
        ui->frame_personnelpage_4->setVisible(true);
    }
}


/**
 * progress bar
 *
 * @author hzc
 */
void SystemCenter::progressBar()
{
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100);
    for (int i = 0; i <= 100; i++){
        for(int j = 0; j < 1000000; j++){
            i = i + 1;
            i = i - 1;
        }
        ui->progressBar->setValue(i);
        QApplication::processEvents();
    }
    ui->progressBar->setVisible(false);
}

/**
 * fast version progress bar
 *
 * @author hzc
 */
void SystemCenter::progressBar_fast()
{
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100);
    for (int i = 0; i <= 100; i++){
        for(int j = 0; j < 300000; j++){
            i = i + 1;
            i = i - 1;
        }
        ui->progressBar->setValue(i);
        QApplication::processEvents();
    }
    ui->progressBar->setVisible(false);
}


/**
 * on_pushButton_2_clicked slot
 *
 * @author hzc
 */
void SystemCenter::on_pushButton_switch_clicked()
{
    QApplication::processEvents();
    Login *lg = new Login;
    connect(this, SIGNAL(stringReturn(QString)), lg, SLOT(showString(QString)));
    emit stringReturn(this->ui->label_2->text());
    this->close();
}

/**
 * download picture
 *
 * @author hzc
 * @param surl pic url
 * @param filePath local file path
 */
void SystemCenter::download(const QString &url, const QString &filePath)
{

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << (quint32) (sizeof(QString));
    out << url;
    out.device()->seek(0);
    m_socket->write(message);

    this->filepath = filePath;

}

/**
 * save picture
 *
 * @author hzc
 * @param reply NetworkReply
 */
void SystemCenter::replyFinished()
{
    QDataStream in(m_socket);
    in.setVersion (QDataStream::Qt_5_7);

    if(dataSize == 0)
    {
       if(m_socket->bytesAvailable() < (qint32)(sizeof(quint32)+sizeof(QString)) )
       {
            return;
       }
       in >> dataSize;
       in >> fileName;
    }

    if(dataSize > qint32(m_socket->bytesAvailable()))
    {
       return;
    }

    QByteArray data;

    in>>data;

    QImage img;
    img.loadFromData(data);

    img.save(DIR + fileName);

    dataSize = 0;
    fileName.clear();
}

void SystemCenter::on_style_change_clicked()
{
    int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont icon_search;
    icon_search.setFamily(fontFamilies.at(0));
    icon_search.setPointSize(24);


    if(style){
        ui->frame->setStyleSheet("QFrame{background:rgba(255, 255, 255, 255);"
                                 "border-image:url(:/bg4.png);}");
        ui->style_change->setFont(icon_search);
        ui->style_change->setText(QChar(0xf204));
        ui->style_change->setStyleSheet("QPushButton{border: 0px; color: white;} "
                                        "QPushButton:hover{border: 0px; color: rgba(15, 128, 255, 190);} ");
    }else{
        ui->frame->setStyleSheet("QFrame{background: rgba(255, 255, 255, 0);"
                                 "border-image:url(:/bg5.png);}");
        ui->style_change->setFont(icon_search);
        ui->style_change->setText(QChar(0xf205));
        ui->style_change->setStyleSheet("QPushButton{border: 0px; color: white;} "
                                        "QPushButton:hover{border: 0px; color: rgba(15, 128, 255, 190);} ");
    }
    style = !style;

    QFile *file = new QFile(CONFIG_DIR);
    if (file->open(QFile::ReadWrite | QFile::Text)){
        QTextStream out(file);
        out << style << "\n";
    }else{
        qDebug()<<"打开失败";
    }
    file->close();
}
