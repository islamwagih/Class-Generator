# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindow.ui'
##
## Created by: Qt User Interface Compiler version 6.4.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QAbstractItemView, QApplication, QComboBox, QFrame,
    QGridLayout, QHBoxLayout, QHeaderView, QLabel,
    QLineEdit, QMainWindow, QMenu, QMenuBar,
    QPushButton, QSizePolicy, QSpacerItem, QStatusBar,
    QToolButton, QTreeWidget, QTreeWidgetItem, QVBoxLayout,
    QWidget)
import resources_rc

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1098, 656)
        MainWindow.setMinimumSize(QSize(800, 600))
        icon = QIcon()
        icon.addFile(u":/icons/configuration.png", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setStyleSheet(u"#MainWindow{\n"
"	background-color: rgb(44, 49, 59);\n"
"}\n"
"\n"
"QMenuBar {\n"
"    background-color: rgb(44, 49, 59);\n"
"}\n"
"\n"
"QMenuBar::height {\n"
"    height: 30px;\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    color: white;\n"
"}\n"
"\n"
"QMenuBar::item:hover {\n"
"    background-color: rgb(51, 57, 68);\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"    background-color: rgb(51, 57, 68);\n"
"}\n"
"\n"
"QMenu {\n"
"    background-color: rgb(44, 49, 59);\n"
"}\n"
"\n"
"QMenu::item {\n"
"    color: white;\n"
"}\n"
"\n"
"QMenu::item:hover {\n"
"    background-color: rgb(51, 57, 68);\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"    background-color: rgb(51, 57, 68);\n"
"}\n"
"")
        self.actionInsert_Child = QAction(MainWindow)
        self.actionInsert_Child.setObjectName(u"actionInsert_Child")
        self.actionInsert_Row = QAction(MainWindow)
        self.actionInsert_Row.setObjectName(u"actionInsert_Row")
        self.actionReset = QAction(MainWindow)
        self.actionReset.setObjectName(u"actionReset")
        self.actionSave = QAction(MainWindow)
        self.actionSave.setObjectName(u"actionSave")
        self.actionLoad = QAction(MainWindow)
        self.actionLoad.setObjectName(u"actionLoad")
        self.actionRemove_Row = QAction(MainWindow)
        self.actionRemove_Row.setObjectName(u"actionRemove_Row")
        self.centralWidget = QWidget(MainWindow)
        self.centralWidget.setObjectName(u"centralWidget")
        self.centralWidget.setStyleSheet(u"")
        self.verticalLayout = QVBoxLayout(self.centralWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.frameDirectory = QFrame(self.centralWidget)
        self.frameDirectory.setObjectName(u"frameDirectory")
        self.frameDirectory.setStyleSheet(u"border-radius: 15px;\n"
"background-color: rgb(37, 40, 50);")
        self.frameDirectory.setFrameShape(QFrame.StyledPanel)
        self.frameDirectory.setFrameShadow(QFrame.Raised)
        self.verticalLayout_2 = QVBoxLayout(self.frameDirectory)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.outEdit = QLineEdit(self.frameDirectory)
        self.outEdit.setObjectName(u"outEdit")
        self.outEdit.setMinimumSize(QSize(0, 40))
        self.outEdit.setStyleSheet(u"QLineEdit{\n"
"	border: 0px solid rgb(37, 39, 48);\n"
"	border-radius: 15px;\n"
"	color: #FFF;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	background-color: rgb(27, 29, 35);\n"
"}\n"
"QLineEdit:hover{\n"
"	border: 2px solid rgb(64, 71, 88)\n"
"}\n"
"QLineEdit:focus{\n"
"	border: 2px solid rgb(91, 101, 124);\n"
"}")

        self.horizontalLayout.addWidget(self.outEdit)

        self.toolButton = QToolButton(self.frameDirectory)
        self.toolButton.setObjectName(u"toolButton")
        self.toolButton.setMinimumSize(QSize(40, 40))
        self.toolButton.setStyleSheet(u"QToolButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(52, 59, 72);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"QToolButton:hover {\n"
"	background-color: rgb(57, 65, 80);\n"
"	border: 2px solid rgb(61, 70, 86);\n"
"}\n"
"QToolButton:pressed {	\n"
"	background-color: rgb(35, 40, 49);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")

        self.horizontalLayout.addWidget(self.toolButton)


        self.verticalLayout_2.addLayout(self.horizontalLayout)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.label = QLabel(self.frameDirectory)
        self.label.setObjectName(u"label")
        font = QFont()
        font.setPointSize(10)
        font.setBold(True)
        self.label.setFont(font)
        self.label.setStyleSheet(u"color: #FFF;")

        self.horizontalLayout_2.addWidget(self.label)

        self.typeComboBox = QComboBox(self.frameDirectory)
        self.typeComboBox.addItem("")
        self.typeComboBox.addItem("")
        self.typeComboBox.addItem("")
        self.typeComboBox.setObjectName(u"typeComboBox")
        sizePolicy = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.typeComboBox.sizePolicy().hasHeightForWidth())
        self.typeComboBox.setSizePolicy(sizePolicy)
        self.typeComboBox.setFont(font)
        self.typeComboBox.setStyleSheet(u"QComboBox{\n"
"	background-color:rgb(27, 29, 35);\n"
"	border: 0px;\n"
"	color: #fff;\n"
"	padding-left: 15px;\n"
"	height: 30px;\n"
"}\n"
"QComboBox::hover{\n"
"	border: 2px solid rgb(64, 71, 88);\n"
"}\n"
"QComboBox::drop-down {\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 23px;\n"
"	border-left-width: 3px;\n"
"	border-left-color: rgba(39, 44, 54, 150);\n"
"	border-left-style: solid;\n"
"	border-top-right-radius: 3px;\n"
"	border-bottom-right-radius: 3px;\n"
"	image: url(:/icons/arrowDown.png);\n"
" }\n"
"QComboBox::disabled {\n"
"	background-color: #3f3f3f;\n"
"    color: #656565;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color:rgb(27, 29, 35);\n"
"	border: 0px;\n"
"	color: #fff;\n"
"    selection-background-color: rgb(64, 71, 88);\n"
"}")

        self.horizontalLayout_2.addWidget(self.typeComboBox)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)


        self.verticalLayout.addWidget(self.frameDirectory)

        self.frameButtons = QFrame(self.centralWidget)
        self.frameButtons.setObjectName(u"frameButtons")
        self.frameButtons.setStyleSheet(u"border-radius: 15px;\n"
"background-color: rgb(37, 40, 50);\n"
"")
        self.frameButtons.setFrameShape(QFrame.StyledPanel)
        self.frameButtons.setFrameShadow(QFrame.Raised)
        self.gridLayout_2 = QGridLayout(self.frameButtons)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.insertChildBtn = QPushButton(self.frameButtons)
        self.insertChildBtn.setObjectName(u"insertChildBtn")
        self.insertChildBtn.setMinimumSize(QSize(200, 35))
        self.insertChildBtn.setFont(font)
        self.insertChildBtn.setStyleSheet(u"QPushButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(33, 188, 180);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {	\n"
"	background-color: rgb(84, 195, 195);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}\n"
"\n"
"\n"
"QPushButton:pressed {	\n"
"	background-color: rgb(25, 154, 147);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")

        self.gridLayout_2.addWidget(self.insertChildBtn, 1, 1, 1, 1)

        self.resetBtn = QPushButton(self.frameButtons)
        self.resetBtn.setObjectName(u"resetBtn")
        self.resetBtn.setMinimumSize(QSize(200, 35))
        self.resetBtn.setFont(font)
        self.resetBtn.setStyleSheet(u"QPushButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(241, 89, 90);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {	\n"
"	background-color: rgb(255, 102, 102);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}\n"
"\n"
"QPushButton:pressed {	\n"
"	background-color: rgb(202, 75, 75);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")

        self.gridLayout_2.addWidget(self.resetBtn, 1, 4, 1, 1)

        self.removeRowBtn = QPushButton(self.frameButtons)
        self.removeRowBtn.setObjectName(u"removeRowBtn")
        self.removeRowBtn.setMinimumSize(QSize(200, 35))
        self.removeRowBtn.setFont(font)
        self.removeRowBtn.setStyleSheet(u"QPushButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(241, 89, 90);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {	\n"
"	background-color: rgb(255, 102, 102);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}\n"
"\n"
"QPushButton:pressed {	\n"
"	background-color: rgb(202, 75, 75);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")

        self.gridLayout_2.addWidget(self.removeRowBtn, 1, 3, 1, 1)

        self.insertRowBn = QPushButton(self.frameButtons)
        self.insertRowBn.setObjectName(u"insertRowBn")
        self.insertRowBn.setMinimumSize(QSize(200, 35))
        self.insertRowBn.setFont(font)
        self.insertRowBn.setStyleSheet(u"QPushButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(33, 188, 180);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {	\n"
"	background-color: rgb(84, 195, 195);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}\n"
"\n"
"\n"
"QPushButton:pressed {	\n"
"	background-color: rgb(25, 154, 147);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")

        self.gridLayout_2.addWidget(self.insertRowBn, 1, 0, 1, 1)

        self.resetBtn.raise_()
        self.removeRowBtn.raise_()
        self.insertChildBtn.raise_()
        self.insertRowBn.raise_()

        self.verticalLayout.addWidget(self.frameButtons)

        self.frameTable = QFrame(self.centralWidget)
        self.frameTable.setObjectName(u"frameTable")
        self.frameTable.setStyleSheet(u"QFrame {	\n"
"	border-radius: 15px;\n"
"	background-color: rgb(37, 40, 50);\n"
"}\n"
"QFrame QScrollBar:horizontal {\n"
"    border: none;\n"
"    background: rgb(52, 59, 72);\n"
"    height: 14px;\n"
"    margin: 0px 21px 0 21px;\n"
"	border-radius: 0px;\n"
"}\n"
" QFrame QScrollBar:vertical {\n"
"	border: none;\n"
"    background: rgb(52, 59, 72);\n"
"    width: 14px;\n"
"    margin: 21px 0 21px 0;\n"
"	border-radius: 0px;\n"
" }\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background: rgb(85, 170, 255);\n"
"    min-width: 25px;\n"
"	border-radius: 7px\n"
"}\n"
"QScrollBar::add-line:horizontal {\n"
"    border: none;\n"
"    background: rgb(55, 63, 77);\n"
"    width: 20px;\n"
"	border-top-right-radius: 7px;\n"
"    border-bottom-right-radius: 7px;\n"
"    subcontrol-position: right;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::sub-line:horizontal {\n"
"    border: none;\n"
"    background: rgb(55, 63, 77);\n"
"    width: 20px;\n"
"	border-top-left-radius: 7px;\n"
"    border-bottom-left-radi"
                        "us: 7px;\n"
"    subcontrol-position: left;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::up-arrow:horizontal, QScrollBar::down-arrow:horizontal\n"
"{\n"
"     background: none;\n"
"}\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"     background: none;\n"
"}\n"
" QScrollBar::handle:vertical {	\n"
"	background: rgb(85, 170, 255);\n"
"    min-height: 25px;\n"
"	border-radius: 7px\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"     border: none;\n"
"    background: rgb(55, 63, 77);\n"
"     height: 20px;\n"
"	border-bottom-left-radius: 7px;\n"
"    border-bottom-right-radius: 7px;\n"
"     subcontrol-position: bottom;\n"
"     subcontrol-origin: margin;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border: none;\n"
"    background: rgb(55, 63, 77);\n"
"     height: 20px;\n"
"	border-top-left-radius: 7px;\n"
"    border-top-right-radius: 7px;\n"
"     subcontrol-position: top;\n"
"     subcontrol-origin: margin;\n"
" }\n"
" QScrollBar::up-arrow:vertical, QScrollBar::"
                        "down-arrow:vertical {\n"
"     background: none;\n"
" }\n"
"\n"
" QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"     background: none;\n"
" }\n"
"\n"
"/***********************/\n"
"\n"
"/*******************/\n"
"\n"
"QTreeWidget {	\n"
"	background-color: rgb(39, 44, 54);\n"
"	padding: 10px;\n"
"	border-radius: 10px;\n"
"	gridline-color: rgb(49, 54, 65);\n"
"}\n"
"\n"
"QTreeWidget::item:selected{\n"
"	background-color: rgb(85, 170, 255);\n"
"	background-color: rgb(44, 49, 59);\n"
"}\n"
"/***********/\n"
"QHeaderView::section{\n"
"	Background-color: rgb(39, 44, 54);\n"
"	border: 1px solid rgb(44, 49, 60);\n"
"	color: white;\n"
"	border-style: none;\n"
"    border-bottom: 1px solid rgb(44, 49, 60);\n"
"    border-right: 1px solid rgb(44, 49, 60);\n"
"}\n"
"/*****/\n"
"QLineEdit{\n"
"	border: 0px solid rgb(27, 29, 35); \n"
"	padding: 2px;\n"
"	color: #FFF;\n"
"	background-color: rgb(27, 29, 35);\n"
"	border-radius: 10px;\n"
"	margin-left:10 px;\n"
"	margin-right:10 px;\n"
"	margin-bottom: 2px;"
                        "\n"
"}\n"
"QLineEdit:hover{\n"
"	border: 2px solid rgb(64, 71, 88)\n"
"}\n"
"QLineEdit:focus{\n"
"	border: 2px solid rgb(91, 101, 124);\n"
"}\n"
"QLineEdit:disabled {\n"
"    border: 2px solid rgb(98, 98, 98);\n"
"    background-color: rgb(61, 61, 61);\n"
"    color: rgb(128, 128, 128);\n"
"}\n"
"/***********/\n"
"QComboBox{\n"
"	background-color:rgb(27, 29, 35);\n"
"	border-radius: 10px;\n"
"	border: 0px;\n"
"	color: #fff;\n"
"	padding-left: 7px;\n"
"	margin-bottom: 2px;\n"
"}\n"
"QComboBox::hover{\n"
"	border: 2px solid rgb(64, 71, 88);\n"
"}\n"
"QComboBox::drop-down {\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 23px;\n"
"	border-left-width: 3px;\n"
"	border-left-color: rgba(39, 44, 54, 150);\n"
"	border-left-style: solid;\n"
"	border-top-right-radius: 3px;\n"
"	border-bottom-right-radius: 3px;\n"
"	image: url(:/icons/arrowDown.png);\n"
" }\n"
"QComboBox::disabled {\n"
"	background-color: #3f3f3f;\n"
"    color: #656565;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    ba"
                        "ckground-color:rgb(27, 29, 35);\n"
"	border: 0px;\n"
"	color: #fff;\n"
"    selection-background-color: rgb(64, 71, 88);\n"
"}\n"
"")
        self.frameTable.setFrameShape(QFrame.StyledPanel)
        self.frameTable.setFrameShadow(QFrame.Raised)
        self.gridLayout_4 = QGridLayout(self.frameTable)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.configTree = QTreeWidget(self.frameTable)
        __qtreewidgetitem = QTreeWidgetItem()
        __qtreewidgetitem.setFont(2, font);
        __qtreewidgetitem.setFont(1, font);
        __qtreewidgetitem.setFont(0, font);
        self.configTree.setHeaderItem(__qtreewidgetitem)
        self.configTree.setObjectName(u"configTree")
        font1 = QFont()
        font1.setPointSize(10)
        self.configTree.setFont(font1)
        self.configTree.setAcceptDrops(False)
        self.configTree.setStyleSheet(u"QTreeWidget::branch:has-siblings:!adjoins-item {\n"
"	image: url(:/icons/vline.png);\n"
"}\n"
"\n"
"/*QTreeWidget::branch:has-siblings:!adjoins-item {\n"
"    border-image: url(vline.png) 0;\n"
"}*/\n"
"\n"
"\n"
"\n"
"QTreeWidget::branch:has-children:!has-siblings:closed,\n"
"QTreeWidget::branch:closed:has-children:has-siblings {\n"
"        border-image: none;\n"
"        image: url(:/icons/branch-closed.png);\n"
"}\n"
"\n"
"QTreeWidget::branch:open:has-children:!has-siblings,\n"
"QTreeWidget::branch:open:has-children:has-siblings  {\n"
"        border-image: none;\n"
"        image: url(:/icons/branch-open.png);\n"
"}")
        self.configTree.setDragDropOverwriteMode(False)
        self.configTree.setDragDropMode(QAbstractItemView.DragDrop)
        self.configTree.setDefaultDropAction(Qt.MoveAction)
        self.configTree.setAlternatingRowColors(False)
        self.configTree.setSelectionMode(QAbstractItemView.NoSelection)
        self.configTree.setSelectionBehavior(QAbstractItemView.SelectItems)
        self.configTree.setIndentation(12)
        self.configTree.setUniformRowHeights(False)
        self.configTree.setAnimated(False)
        self.configTree.setHeaderHidden(False)
        self.configTree.header().setVisible(True)
        self.configTree.header().setCascadingSectionResizes(False)
        self.configTree.header().setHighlightSections(False)
        self.configTree.header().setProperty("showSortIndicator", False)

        self.gridLayout_4.addWidget(self.configTree, 0, 0, 1, 1)


        self.verticalLayout.addWidget(self.frameTable)

        self.frameGenerateButton = QFrame(self.centralWidget)
        self.frameGenerateButton.setObjectName(u"frameGenerateButton")
        self.frameGenerateButton.setStyleSheet(u"border-radius: 15px;\n"
"background-color: rgb(37, 40, 50);\n"
"QPushButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(52, 59, 72);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 65, 80);\n"
"	border: 2px solid rgb(61, 70, 86);\n"
"}\n"
"QPushButton:pressed {	\n"
"	background-color: rgb(35, 40, 49);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")
        self.frameGenerateButton.setFrameShape(QFrame.StyledPanel)
        self.frameGenerateButton.setFrameShadow(QFrame.Raised)
        self.gridLayout_3 = QGridLayout(self.frameGenerateButton)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.generateBtn = QPushButton(self.frameGenerateButton)
        self.generateBtn.setObjectName(u"generateBtn")
        self.generateBtn.setMinimumSize(QSize(200, 35))
        self.generateBtn.setFont(font)
        self.generateBtn.setStyleSheet(u"QPushButton {\n"
"	border: 2px solid rgb(52, 59, 72);\n"
"	background-color: rgb(33, 188, 180);\n"
"	color: rgb(223, 223, 223);\n"
"	border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {	\n"
"	background-color: rgb(84, 195, 195);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}\n"
"\n"
"\n"
"QPushButton:pressed {	\n"
"	background-color: rgb(25, 154, 147);\n"
"	border: 2px solid rgb(43, 50, 61);\n"
"}")

        self.gridLayout_3.addWidget(self.generateBtn, 0, 0, 1, 1)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_3.addItem(self.horizontalSpacer, 0, 1, 1, 1)


        self.verticalLayout.addWidget(self.frameGenerateButton)

        MainWindow.setCentralWidget(self.centralWidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1098, 25))
        self.menuFile = QMenu(self.menubar)
        self.menuFile.setObjectName(u"menuFile")
        self.menuActions = QMenu(self.menubar)
        self.menuActions.setObjectName(u"menuActions")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuActions.menuAction())
        self.menuFile.addAction(self.actionSave)
        self.menuFile.addAction(self.actionLoad)
        self.menuActions.addAction(self.actionInsert_Row)
        self.menuActions.addAction(self.actionInsert_Child)
        self.menuActions.addSeparator()
        self.menuActions.addAction(self.actionRemove_Row)
        self.menuActions.addAction(self.actionReset)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Class Generator", None))
        self.actionInsert_Child.setText(QCoreApplication.translate("MainWindow", u"Insert Child", None))
#if QT_CONFIG(shortcut)
        self.actionInsert_Child.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+I, Ctrl+H", None))
#endif // QT_CONFIG(shortcut)
        self.actionInsert_Row.setText(QCoreApplication.translate("MainWindow", u"Insert Row", None))
#if QT_CONFIG(shortcut)
        self.actionInsert_Row.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+I, Ctrl+W", None))
#endif // QT_CONFIG(shortcut)
        self.actionReset.setText(QCoreApplication.translate("MainWindow", u"Reset", None))
#if QT_CONFIG(shortcut)
        self.actionReset.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+R, Ctrl+A", None))
#endif // QT_CONFIG(shortcut)
        self.actionSave.setText(QCoreApplication.translate("MainWindow", u"Save", None))
#if QT_CONFIG(shortcut)
        self.actionSave.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+S", None))
#endif // QT_CONFIG(shortcut)
        self.actionLoad.setText(QCoreApplication.translate("MainWindow", u"Load", None))
#if QT_CONFIG(shortcut)
        self.actionLoad.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+L", None))
#endif // QT_CONFIG(shortcut)
        self.actionRemove_Row.setText(QCoreApplication.translate("MainWindow", u"Remove Row", None))
#if QT_CONFIG(shortcut)
        self.actionRemove_Row.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+R, Ctrl+W", None))
#endif // QT_CONFIG(shortcut)
        self.outEdit.setPlaceholderText(QCoreApplication.translate("MainWindow", u"Output Directory", None))
        self.toolButton.setText(QCoreApplication.translate("MainWindow", u"...", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"File Type", None))
        self.typeComboBox.setItemText(0, QCoreApplication.translate("MainWindow", u"JSON", None))
        self.typeComboBox.setItemText(1, QCoreApplication.translate("MainWindow", u"XML", None))
        self.typeComboBox.setItemText(2, QCoreApplication.translate("MainWindow", u"INI", None))

        self.insertChildBtn.setText(QCoreApplication.translate("MainWindow", u"Insert Child", None))
        self.resetBtn.setText(QCoreApplication.translate("MainWindow", u"Reset", None))
        self.removeRowBtn.setText(QCoreApplication.translate("MainWindow", u"Remove Row", None))
        self.insertRowBn.setText(QCoreApplication.translate("MainWindow", u"Insert Row", None))
        ___qtreewidgetitem = self.configTree.headerItem()
        ___qtreewidgetitem.setText(2, QCoreApplication.translate("MainWindow", u"Constraints", None));
        ___qtreewidgetitem.setText(1, QCoreApplication.translate("MainWindow", u"Type", None));
        ___qtreewidgetitem.setText(0, QCoreApplication.translate("MainWindow", u"Name", None));
        self.generateBtn.setText(QCoreApplication.translate("MainWindow", u"Generate Class", None))
        self.menuFile.setTitle(QCoreApplication.translate("MainWindow", u"File", None))
        self.menuActions.setTitle(QCoreApplication.translate("MainWindow", u"Actions", None))
    # retranslateUi

