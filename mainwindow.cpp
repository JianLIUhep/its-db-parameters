#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QtCore>
#include <QtGui>
#include <deque>
#include <mutex>
#include <qapplication.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <QFileDialog>
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TText.h"
#include "TStyle.h"
#include "TColor.h"



using namespace std;

//ActivityTypeID = 852; //out barrel FPC electrical test
//ActivityTypeID = 1043; //Outer Barrel FPC shipment
//ActivityTypeID = 542; //OB-HIC assembly
//ActivityTypeID = 901; //OB-HIC impedance test
//ActivityTypeID = 601; //OB-HIC qualification test
//ActivityTypeID = 661; //OB-HIC endurance test
//ActivityTypeID = 1042; //OB-HIC shipment
//ActivityTypeID = 681; //reception test
//ActivityTypeID = 742; //Tab cut
//ActivityTypeID = 801; //fast power test
//ActivityTypeID = 881; //HS qualification test
//ActivityTypeID = 1141; //Stave qualification test
//ActivityTypeID = 1201; //Stave reception test
//ActivityTypeID = 761; //PBs soldering

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//single module button
void MainWindow::on_get_clicked()
{

  string moduleName;
  moduleName = ui->moduleID->toPlainText().toStdString().c_str();
  this->get_module_info(moduleName);

}

void MainWindow::get_module_info(string moduleName){
	
	  MStaveR para_reception, para_fast, para_HS, para_stave, para_qualification, para_staver;
	  int fDatabasetype=0;

	  AlpideDB *theDB = new AlpideDB(fDatabasetype);
	  para_reception=this->getMReceptionDB(theDB, moduleName,1);
	  para_HS=this->getHSDB(theDB, moduleName,3);
	  para_fast=this->getFastDB(theDB, moduleName,2);
	  para_stave=this->getStaveDB(theDB, moduleName,4);
	  para_qualification=this->getMQDB(theDB, moduleName,0);
	  para_staver=this->getStaveRDB(theDB, moduleName,5);
	  this->plot_pixel(para_qualification, para_reception, para_HS, para_stave, para_staver);
	  this->plot_current(para_qualification,para_reception, para_fast, para_HS, para_stave, para_staver);
	  
	  
	  delete theDB;
	
}

//stave info button
void MainWindow::on_get_stave_clicked()
{

  string staveName;

  
  int fDatabasetype=0;
  staveName = ui->stave_id->toPlainText().toStdString().c_str();

  AlpideDB *theDB = new AlpideDB(fDatabasetype);
  this->getstavecompDB(theDB, staveName);

  stave_parameters(staveName);
  
  
  delete theDB;
}



void MainWindow::on_get_module_l1_clicked()
{

  string moduleName=ui->module_l_1->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_1->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_l2_clicked()
{

  string moduleName=ui->module_l_2->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_2->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_l3_clicked()
{

  string moduleName=ui->module_l_3->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_3->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_l4_clicked()
{

  string moduleName=ui->module_l_4->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_4->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_l5_clicked()
{

  string moduleName=ui->module_l_5->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_5->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_l6_clicked()
{

  string moduleName=ui->module_l_6->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_6->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_l7_clicked()
{

  string moduleName=ui->module_l_7->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_l_7->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r1_clicked()
{

  string moduleName=ui->module_r_1->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_1->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r2_clicked()
{

  string moduleName=ui->module_r_2->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_2->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r3_clicked()
{

  string moduleName=ui->module_r_3->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_3->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r4_clicked()
{

  string moduleName=ui->module_r_4->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_4->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r5_clicked()
{

  string moduleName=ui->module_r_5->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_5->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r6_clicked()
{

  string moduleName=ui->module_r_6->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_6->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}

void MainWindow::on_get_module_r7_clicked()
{

  string moduleName=ui->module_r_7->toPlainText().toStdString().c_str();
  QString Qmodulename=ui->module_r_7->toPlainText();
  ui->moduleID->setPlainText(Qmodulename);
  this->get_module_info(moduleName);
  ui->Stave_GUI->setCurrentIndex(1);
  
}


void MainWindow::on_bad_pixels_clicked(){
    string modulename, pic;
	modulename = ui->moduleID->toPlainText().toStdString().c_str();
    pic = "Badpix_"+modulename+".png";
	QString qpic;  
    qpic= QString::fromStdString(pic);

	  QGraphicsScene* scene = new QGraphicsScene();
	  QPixmap pixmap(qpic);
	  scene->addPixmap(pixmap);
	  ui->plot1->setScene(scene);
	  ui->plot1->show();
	
}


void MainWindow::on_current_clicked(){
	
    string modulename, pic;
	modulename = ui->moduleID->toPlainText().toStdString().c_str();
    pic = "Current_"+modulename+".png";
	QString qpic;  
    qpic= QString::fromStdString(pic);
    
	  QGraphicsScene* scene = new QGraphicsScene();
	  QPixmap pixmap(qpic);
	  scene->addPixmap(pixmap);
	  ui->plot1->setScene(scene);
	  ui->plot1->show();
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//get the module qualification
//
////////////////////////////////////////////////////////////////////////////////////////////////
struct MainWindow::MStaveR MainWindow::getMQDB(AlpideDB *theDB, string hicname, const int index)
{
	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
	MStaveR para=getmodulepara(theDB, hicname, index);
	//cout<<para.error<<endl;
	if (para.error!="No activities exit!"){
	  idda= QString::fromStdString(to_string(para.IDDA));
	  iddd= QString::fromStdString(to_string(para.IDDD));
  	  iddac= QString::fromStdString(to_string(para.IDDAC));
  	  idddc= QString::fromStdString(to_string(para.IDDDC));
	  pixel= QString::fromStdString(to_string(para.pixels));
  	  pixelth= QString::fromStdString(to_string(para.pixelsth));
  	  thmax= QString::fromStdString(to_string(para.ThMax));
  	  thmin= QString::fromStdString(to_string(para.ThMin));
  	  noise= QString::fromStdString(to_string(para.Noise));
  	  noisy= QString::fromStdString(to_string(para.Noisy));
  	  noisym= QString::fromStdString(to_string(para.NoisyM));

  	  
  	  ui->info_0->setPlainText("IDDA = "+idda+" A");
  	  ui->info_0->appendPlainText("IDDA clocked = "+iddac+" A"); // \n
  	  ui->info_0->appendPlainText("IDDD = "+iddd+" A"); // \n
  	  ui->info_0->appendPlainText("IDDD clocked = "+idddc+" A"); // \n
  	  ui->info_0->appendPlainText("Bad pixels digital (nominal) = "+pixel+" ");
  	  ui->info_0->appendPlainText("Bad pixels th (0 V) = "+pixelth+" ");
  	  ui->info_0->appendPlainText("Maximum chip TH (0 V) = "+thmax+" ");
  	  ui->info_0->appendPlainText("Minimum chip TH (0 V) = "+thmin+" ");
  	  ui->info_0->appendPlainText("Average noise (0 V) = "+noise+" ");
  	  ui->info_0->appendPlainText("Noisy Pixels (0 V) = "+noisy+" ");
  	  ui->info_0->appendPlainText("Noisy Pixels masked (0 V) = "+noisym+" ");
  	  
  	  
  	  
	}else{
  
	  ui->info_0->setPlainText("No activities exit!");
	}
	return para;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//get the module reception
//
////////////////////////////////////////////////////////////////////////////////////////////////  
struct MainWindow::MStaveR MainWindow::getMReceptionDB(AlpideDB *theDB, string hicname, const int index)
{
	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
	MStaveR para=getmodulepara(theDB, hicname, index);
	//cout<<para.error<<endl;
	if (para.error!="No activities exit!"){
	  idda= QString::fromStdString(to_string(para.IDDA));
	  iddd= QString::fromStdString(to_string(para.IDDD));
  	  iddac= QString::fromStdString(to_string(para.IDDAC));
  	  idddc= QString::fromStdString(to_string(para.IDDDC));
	  pixel= QString::fromStdString(to_string(para.pixels));
  	  pixelth= QString::fromStdString(to_string(para.pixelsth));
  	  thmax= QString::fromStdString(to_string(para.ThMax));
  	  thmin= QString::fromStdString(to_string(para.ThMin));
  	  noise= QString::fromStdString(to_string(para.Noise));
  	  noisy= QString::fromStdString(to_string(para.Noisy));
  	  noisym= QString::fromStdString(to_string(para.NoisyM));

  	  
  	  ui->info_1->setPlainText("IDDA = "+idda+" A");
  	  ui->info_1->appendPlainText("IDDA clocked = "+iddac+" A"); // \n
  	  ui->info_1->appendPlainText("IDDD = "+iddd+" A"); // \n
  	  ui->info_1->appendPlainText("IDDD clocked = "+idddc+" A"); // \n
  	  ui->info_1->appendPlainText("Bad pixels digital (nominal) = "+pixel+" ");
  	  ui->info_1->appendPlainText("Bad pixels th (0 V) = "+pixelth+" ");
  	  ui->info_1->appendPlainText("Maximum chip TH (0 V) = "+thmax+" ");
  	  ui->info_1->appendPlainText("Minimum chip TH (0 V) = "+thmin+" ");
  	  ui->info_1->appendPlainText("Average noise (0 V) = "+noise+" ");
  	  ui->info_1->appendPlainText("Noisy Pixels (0 V) = "+noisy+" ");
  	  ui->info_1->appendPlainText("Noisy Pixels masked (0 V) = "+noisym+" ");
  	  
  	  
  	  
	}else{
  
	  ui->info_1->setPlainText("No activities exit!");
	}
	return para;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//get the fast power
//
////////////////////////////////////////////////////////////////////////////////////////////////
  struct MainWindow::MStaveR MainWindow::getFastDB(AlpideDB *theDB, string hicname, const int index)
  {
  	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
  	MStaveR para=getmodulepara(theDB, hicname, index);
  	//cout<<para.error<<endl;
  	if (para.error!="No activities exit!"){
  	  idda= QString::fromStdString(to_string(para.IDDA));
  	  iddd= QString::fromStdString(to_string(para.IDDD));
    	  iddac= QString::fromStdString(to_string(para.IDDAC));
    	  idddc= QString::fromStdString(to_string(para.IDDDC));
  	  pixel= QString::fromStdString(to_string(para.pixels));
    	  pixelth= QString::fromStdString(to_string(para.pixelsth));
    	  thmax= QString::fromStdString(to_string(para.ThMax));
    	  thmin= QString::fromStdString(to_string(para.ThMin));
    	  noise= QString::fromStdString(to_string(para.Noise));
    	  noisy= QString::fromStdString(to_string(para.Noisy));
    	  noisym= QString::fromStdString(to_string(para.NoisyM));

    	  
    	  ui->info_2->setPlainText("IDDA = "+idda+" A");
    	  ui->info_2->appendPlainText("IDDA clocked = "+iddac+" A"); // \n
    	  ui->info_2->appendPlainText("IDDD = "+iddd+" A"); // \n
    	  ui->info_2->appendPlainText("IDDD clocked = "+idddc+" A"); // \n
    	  ui->info_2->appendPlainText("Bad pixels digital (nominal) = "+pixel+" ");
    	  ui->info_2->appendPlainText("Bad pixels th (0 V) = "+pixelth+" ");
    	  ui->info_2->appendPlainText("Maximum chip TH (0 V) = "+thmax+" ");
    	  ui->info_2->appendPlainText("Minimum chip TH (0 V) = "+thmin+" ");
    	  ui->info_2->appendPlainText("Average noise (0 V) = "+noise+" ");
    	  ui->info_2->appendPlainText("Noisy Pixels (0 V) = "+noisy+" ");
    	  ui->info_2->appendPlainText("Noisy Pixels masked (0 V) = "+noisym+" ");
    	  
    	  
    	  
  	}else{
    
  	  ui->info_2->setPlainText("No activities exit!");
  	}
  	return para;
  }



/////////////////////////////////////////////////////////////////////////////////////////////////
//get the HS
//
////////////////////////////////////////////////////////////////////////////////////////////////
struct MainWindow::MStaveR MainWindow::getHSDB(AlpideDB *theDB, string hicname, const int index)
{
	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
	MStaveR para=getmodulepara(theDB, hicname, index);
	//cout<<para.error<<endl;
	if (para.error!="No activities exit!"){
	  idda= QString::fromStdString(to_string(para.IDDA));
	  iddd= QString::fromStdString(to_string(para.IDDD));
  	  iddac= QString::fromStdString(to_string(para.IDDAC));
  	  idddc= QString::fromStdString(to_string(para.IDDDC));
	  pixel= QString::fromStdString(to_string(para.pixels));
  	  pixelth= QString::fromStdString(to_string(para.pixelsth));
  	  thmax= QString::fromStdString(to_string(para.ThMax));
  	  thmin= QString::fromStdString(to_string(para.ThMin));
  	  noise= QString::fromStdString(to_string(para.Noise));
  	  noisy= QString::fromStdString(to_string(para.Noisy));
  	  noisym= QString::fromStdString(to_string(para.NoisyM));

  	  
  	  ui->info_3->setPlainText("IDDA = "+idda+" A");
  	  ui->info_3->appendPlainText("IDDA clocked = "+iddac+" A"); // \n
  	  ui->info_3->appendPlainText("IDDD = "+iddd+" A"); // \n
  	  ui->info_3->appendPlainText("IDDD clocked = "+idddc+" A"); // \n
  	  ui->info_3->appendPlainText("Bad pixels digital (nominal) = "+pixel+" ");
  	  ui->info_3->appendPlainText("Bad pixels th (0 V) = "+pixelth+" ");
  	  ui->info_3->appendPlainText("Maximum chip TH (0 V) = "+thmax+" ");
  	  ui->info_3->appendPlainText("Minimum chip TH (0 V) = "+thmin+" ");
  	  ui->info_3->appendPlainText("Average noise (0 V) = "+noise+" ");
  	  ui->info_3->appendPlainText("Noisy Pixels (0 V) = "+noisy+" ");
  	  ui->info_3->appendPlainText("Noisy Pixels masked (0 V) = "+noisym+" ");
  	  
  	  
  	  
	}else{
  
	  ui->info_3->setPlainText("No activities exit!");
	}
	return para;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//get the stave qualification
////////////////////////////////////////////////////////////////////////////////////////////////
struct MainWindow::MStaveR MainWindow::getStaveDB(AlpideDB *theDB, string hicname, const int index)
{
	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
	MStaveR para=getmodulepara(theDB, hicname, index);
	//cout<<para.error<<endl;
	if (para.error!="No activities exit!"){
	  idda= QString::fromStdString(to_string(para.IDDA));
	  iddd= QString::fromStdString(to_string(para.IDDD));
  	  iddac= QString::fromStdString(to_string(para.IDDAC));
  	  idddc= QString::fromStdString(to_string(para.IDDDC));
	  pixel= QString::fromStdString(to_string(para.pixels));
  	  pixelth= QString::fromStdString(to_string(para.pixelsth));
  	  thmax= QString::fromStdString(to_string(para.ThMax));
  	  thmin= QString::fromStdString(to_string(para.ThMin));
  	  noise= QString::fromStdString(to_string(para.Noise));
  	  noisy= QString::fromStdString(to_string(para.Noisy));
  	  noisym= QString::fromStdString(to_string(para.NoisyM));

  	  
  	  ui->info_4->setPlainText("IDDA = "+idda+" A");
  	  ui->info_4->appendPlainText("IDDA clocked = "+iddac+" A"); // \n
  	  ui->info_4->appendPlainText("IDDD = "+iddd+" A"); // \n
  	  ui->info_4->appendPlainText("IDDD clocked = "+idddc+" A"); // \n
  	  ui->info_4->appendPlainText("Bad pixels digital (nominal) = "+pixel+" ");
  	  ui->info_4->appendPlainText("Bad pixels th (0 V) = "+pixelth+" ");
  	  ui->info_4->appendPlainText("Maximum chip TH (0 V) = "+thmax+" ");
  	  ui->info_4->appendPlainText("Minimum chip TH (0 V) = "+thmin+" ");
  	  ui->info_4->appendPlainText("Average noise (0 V) = "+noise+" ");
  	  ui->info_4->appendPlainText("Noisy Pixels (0 V) = "+noisy+" ");
  	  ui->info_4->appendPlainText("Noisy Pixels masked (0 V) = "+noisym+" ");
  	  
  	  
  	  
	}else{
  
	  ui->info_4->setPlainText("No activities exit!");
	}
	return para;
}


struct MainWindow::MStaveR MainWindow::getmodulepara(AlpideDB *theDB, string hicname, const int index){
	
    ActivityDB *theActivityTable = new ActivityDB(theDB);
    MStaveR para;
    int ProjectID = 383;//ITS upgrade project
    int ActivityTypeID;
    para.name=hicname;

	switch (index){
	    	
	    	case 0:     		
	    		ActivityTypeID=601;
	    	    break;
	    	case 1:     		
	    		ActivityTypeID=681;
	    		break;
	    	case 2:     		
	    		ActivityTypeID=801;
	    		break;
	    	case 3:     		
	    		ActivityTypeID=881;
	    		break;
	    	case 4:     		
	    		ActivityTypeID=1141;
	    		break;
	    	case 5:     		
	    		ActivityTypeID=1201;
	    		break;	    		       	    		
	    		
	    	default:
	    		break;
	}
	  vector<ActivityDB::activityShort> *act1 = theActivityTable->GetActivityList(ProjectID, ActivityTypeID);
	  
	  int i=0;
	  size_t pos;
	 
	   do {
		   pos = act1->at(i).Name.find(hicname);
		   i++;
	   } while (pos == string::npos && i<act1->size());
	   
	if (i<act1->size()){

	  int ActivityID=act1->at(i-1).ID;
	  ActivityDB::activityLong Act;
	  theActivityTable->Read(ActivityID, &Act);

	  for (unsigned int i = 0; i < Act.Parameters.size(); i++) {
	  
		  if (Act.Parameters.at(i).Type.Parameter.Name == "IDDA"){
		  para.IDDA = Act.Parameters.at(i).Value;
		  }
		  if (Act.Parameters.at(i).Type.Parameter.Name == "IDDD"){
		  para.IDDD = Act.Parameters.at(i).Value;
		  }	  
		  if (Act.Parameters.at(i).Type.Parameter.Name == "Bad pixels digital (nominal)"){
		  para.pixels = Act.Parameters.at(i).Value;
		  }	  
	  	  if (Act.Parameters.at(i).Type.Parameter.Name == "IDDA clocked"){
	  	  para.IDDAC = Act.Parameters.at(i).Value;
	  	  }
	  	  if (Act.Parameters.at(i).Type.Parameter.Name == "IDDD clocked"){
	  	  para.IDDDC = Act.Parameters.at(i).Value;
	  	  }	   
		  if (Act.Parameters.at(i).Type.Parameter.Name == "Dead pixels threshold tuned 0V"){
		  	  para.pixelsth = Act.Parameters.at(i).Value;
		  	  //pixelth= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
		  }	  
		  if (Act.Parameters.at(i).Type.Parameter.Name == "Maximum chip avg threshold tuned 0V"){
		    	  para.ThMax = Act.Parameters.at(i).Value;
		    	 // thmax= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
		    	  }	  

		    	  if (Act.Parameters.at(i).Type.Parameter.Name == "Minimum chip avg threshold tuned 0V"){
		    	  para.ThMin = Act.Parameters.at(i).Value;
		    	 // thmin= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
		    	  }	  
		    	
		    	  if (Act.Parameters.at(i).Type.Parameter.Name == "Average noise threshold tuned 0V"){
		    	  para.Noise = Act.Parameters.at(i).Value;
		    	 // noise= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
		    	  }	    	
		    	

		    	  if (Act.Parameters.at(i).Type.Parameter.Name == "Noisy pixels 0V"){
		    	  para.Noisy = Act.Parameters.at(i).Value;
		    	 // noisy= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
		    	  }	    
		    	  
		    	  
		    	  if (Act.Parameters.at(i).Type.Parameter.Name == "Noisy pixels masked 0V"){
		    	  para.NoisyM = Act.Parameters.at(i).Value;
		    	 // noisym= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
		    	  }	    
		  
		  
	  }
	} else {
		para.error="No activities exit!";
		}

		return para;	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//get the stave reception
//
////////////////////////////////////////////////////////////////////////////////////////////////
struct MainWindow::MStaveR MainWindow::getStaveRDB(AlpideDB *theDB, string hicname, const int index)
{
	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
	MStaveR para=getmodulepara(theDB, hicname, index);
	//cout<<para.error<<endl;
	if (para.error!="No activities exit!"){
	  idda= QString::fromStdString(to_string(para.IDDA));
	  iddd= QString::fromStdString(to_string(para.IDDD));
  	  iddac= QString::fromStdString(to_string(para.IDDAC));
  	  idddc= QString::fromStdString(to_string(para.IDDDC));
	  pixel= QString::fromStdString(to_string(para.pixels));
  	  pixelth= QString::fromStdString(to_string(para.pixelsth));
  	  thmax= QString::fromStdString(to_string(para.ThMax));
  	  thmin= QString::fromStdString(to_string(para.ThMin));
  	  noise= QString::fromStdString(to_string(para.Noise));
  	  noisy= QString::fromStdString(to_string(para.Noisy));
  	  noisym= QString::fromStdString(to_string(para.NoisyM));

  	  
  	  ui->info_5->setPlainText("IDDA = "+idda+" A");
  	  ui->info_5->appendPlainText("IDDA clocked = "+iddac+" A"); // \n
  	  ui->info_5->appendPlainText("IDDD = "+iddd+" A"); // \n
  	  ui->info_5->appendPlainText("IDDD clocked = "+idddc+" A"); // \n
  	  ui->info_5->appendPlainText("Bad pixels digital (nominal) = "+pixel+" ");
  	  ui->info_5->appendPlainText("Bad pixels th (0 V) = "+pixelth+" ");
  	  ui->info_5->appendPlainText("Maximum chip TH (0 V) = "+thmax+" ");
  	  ui->info_5->appendPlainText("Minimum chip TH (0 V) = "+thmin+" ");
  	  ui->info_5->appendPlainText("Average noise (0 V) = "+noise+" ");
  	  ui->info_5->appendPlainText("Noisy Pixels (0 V) = "+noisy+" ");
  	  ui->info_5->appendPlainText("Noisy Pixels masked (0 V) = "+noisym+" ");
  	  
  	  
  	  
	}else{
  
	  ui->info_5->setPlainText("No activities exit!");
	}
	return para;
}


//draw plots of bad pixels
void MainWindow::plot_pixel(MStaveR qual, MStaveR reception, MStaveR half, MStaveR stave, MStaveR staver){
	
	  //Draw graphs
	  TCanvas *c1 = new TCanvas("pixel","pixel",200,10,700,500);
	  int n=5;
	  //int x[n], y[n];
      int x[n]={1,2,3,4,5};
	  int y[n]={qual.pixels, reception.pixels, half.pixels, stave.pixels, staver.pixels};
	  
	  TGraph* plot = new TGraph(n,x,y);
	  
	  
	  plot->GetXaxis()->SetTitle("Test ");
  ////spectrum->GetXaxis()->SetRangeUser(0,1024);
	  plot->GetYaxis()->SetTitle("Pixel numbers");
  ////spectrum->GetYaxis()->SetTitleOffset(1.65);
	  plot->SetTitle("Bad pixels");
      plot->SetLineColor(4);
      plot->SetLineWidth(3);

	  
	  plot->Draw();
	  //c1->SaveAs("Badpix_"+reception.name+".png");
	  string name="Badpix_"+reception.name+".png";
	  const char* cname = name.c_str();
	  c1->SaveAs(cname);

	
}


void MainWindow::plot_current(MStaveR qual, MStaveR reception, MStaveR fast, MStaveR half, MStaveR stave, MStaveR staver){
	
	  //Draw graphs
	  TCanvas *c1 = new TCanvas("pixel","pixel",200,10,700,500);
	  int n=5;
	  //int x[n], y[n];
      float x[n]={1,2,3,4,5};
	  float y[n]={qual.IDDA, reception.IDDA,  half.IDDA, stave.IDDA, staver.IDDA};
	  float y1[n]={qual.IDDD, reception.IDDD, half.IDDD, stave.IDDD, staver.IDDD};
	 
	  
	  //int k=3;
	  
	  //float xc[n]={1,2,3};
	  float yc[n]={qual.IDDAC, reception.IDDAC, half.IDDAC, stave.IDDAC, staver.IDDAC};
	  float yc1[n]={qual.IDDDC, reception.IDDDC, half.IDDDC, stave.IDDDC, staver.IDDDC};
	  
	  //cout<<"title: "<<reception.name<<endl;
	  
	  string title= "Currents of "+reception.name;
	  const char* ctitle=title.c_str();
	  TGraph* plot = new TGraph(n,x,y);
	  TGraph* plot1 = new TGraph(n,x,y1);
	  TGraph* plot2 = new TGraph(n,x,yc);
	  TGraph* plot3 = new TGraph(n,x,yc1);
      plot->GetYaxis()->SetRangeUser(-0.1,1.3);
      plot->GetXaxis()->SetRangeUser(-0.1,5.9);
      

	  plot->GetXaxis()->SetTitle("Test ");
  ////spectrum->GetXaxis()->SetRangeUser(0,1024);
	  plot->GetYaxis()->SetTitle("I (A)");
  ////spectrum->GetYaxis()->SetTitleOffset(1.65);
	  plot->SetTitle(ctitle);
      plot->SetLineColor(4);
      plot->SetLineWidth(2);
      
      
	  //plot->SetTitle(ctitle);
 
	  
	  plot->Draw();
	  
      plot1->SetLineColor(3);
      plot1->SetLineWidth(2); 
	  
	  plot1->Draw("LP");

	  
	  //plot->Draw();
	  
      plot2->SetLineColor(2);
      plot2->SetLineWidth(2); 
	  
	  plot2->Draw("LP");
	  
      plot3->SetLineColor(1);
      plot3->SetLineWidth(2); 
	  
	  plot3->Draw("LP");
	  
	  TText *t = new TText();
	//  t->SetTextAlign(22);
	  //

	  t->SetTextFont(1);
	  t->SetTextSize(0.025);
	  t->DrawText(0.8, -0.1, "Qualification");
	  t->DrawText(1.8, -0.1, "Reception");
	  //t->DrawText(2.8, -0.1, "Fast power");
	  t->DrawText(2.8, -0.1, "HS");
	  
	  //t->Draw();

	  auto legend = new TLegend(0.1,0.75,0.3,0.9);
	  // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
	  legend->AddEntry(plot,"IDDA configured","l");
	  legend->AddEntry(plot1,"IDDD configured","l");
	  legend->AddEntry(plot2,"IDDA clocked","l");
	  legend->AddEntry(plot3,"IDDD clocked","l");
	   

	   //plot3->GetXaxis()->SetBinLabel(2,"R");
	   
      legend->Draw();
	  

	  
	  
	  string name="Current_"+reception.name+".png";
	  const char* cname = name.c_str();
	  c1->SaveAs(cname);
	

	
}





//////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::getstavecompDB(AlpideDB *theDB, string stavename){
	
	std::vector<TChild> halfStaves;
    std::vector<TChild> hics;

	//OL-Stave 519;
	int g_staveType, g_bareStaveType, g_hsUpperType, g_hsLowerType, g_hicType, HALFSTAVECOMP, NHICS;
    g_staveType     = DbGetComponentTypeId(theDB, "Outer Layer Stave");
	//cout<<"Stave type: "<<g_staveType<<endl;
    g_bareStaveType = DbGetComponentTypeId(theDB, "Outer Layer Stave w/o PB&BB");
    g_hsUpperType   = DbGetComponentTypeId(theDB, "Outer Layer Half-Stave Upper");
    g_hsLowerType   = DbGetComponentTypeId(theDB, "Outer Layer Half-Stave Lower");
    g_hicType = DbGetComponentTypeId(theDB, "Outer Barrel HIC Module");
    HALFSTAVECOMP   = 8;
    NHICS           = 14;
	//cout<<"U type: "<<g_hsUpperType<<endl;

	TChild stave;
	stave.Name=stavename;
	stave.Type=g_staveType;
	stave.Id   = DbGetComponentId(theDB, stave.Type, stave.Name);
	
	ui->info_stave->clear();
	//stave.Id=
	
	std::cout << "Checking DB for stave: " << stave.Name << std::endl;
//	  idda= QString::fromStdString(to_string(Act.Parameters.at(i).Value));
    QString qstavename=QString::fromStdString(stave.Name);
	ui->info_stave->setPlainText("Stave : "+qstavename);
	
	std::vector<TChild> staveChildren;
	int                 nChildren = DbGetListOfChildren(theDB, stave.Id, staveChildren);
    //cout<<"number: "<<nChildren<<endl;
    
    TChild bareStave;
    
    for (unsigned int i = 0; i < staveChildren.size(); i++) {
        if (staveChildren.at(i).Type == g_bareStaveType) {
          bareStave = staveChildren.at(i);
          //found     = true;
         // cout<<"Name:"<<bareStave.Name<<endl;
          ui->info_stave->appendPlainText("Bare Stave: "+QString::fromStdString(bareStave.Name));
        }
      }

    std::vector<TChild> bareStaveChildren;
    int  nChildrenbare = DbGetListOfChildren(theDB, bareStave.Id, bareStaveChildren);
	
   // cout<<"number: "<<nChildrenbare<<endl;
    
    halfStaves.clear();
    hics.clear();

    
    for (unsigned int i = 0; i < bareStaveChildren.size(); i++) {
      if ((bareStaveChildren.at(i).Type == g_hsUpperType) ||
          (bareStaveChildren.at(i).Type == g_hsLowerType)) {
        halfStaves.push_back(bareStaveChildren.at(i));
        //cout << halfStaves.at(i).Name<<endl;
      }
    }
   // cout << halfStaves.at(0).Name<<endl;

    std::vector<TChild> halfStaveChildren;

    for (unsigned int i = 0; i < halfStaves.size(); i++) {
        
    int nChildrenhs = DbGetListOfChildren(theDB, halfStaves.at(i).Id, halfStaveChildren);

    // cout << halfStaves.at(i).Name<<endl;
     ui->info_stave->appendPlainText("Half stave : "+QString::fromStdString(halfStaves.at(i).Name));

      for (unsigned int j = 0; j < halfStaveChildren.size(); j++) {
        if (halfStaveChildren.at(j).Type == g_hicType) {
          hics.push_back(halfStaveChildren.at(j));
         // cout<<"HICs :"<<hics.at(i).Name<<endl;
        }
        
      }

    }
    //

    for (unsigned int j = 0; j < hics.size(); j++) {
    
	QString number= QString::fromStdString(to_string(j));
	QString name= QString::fromStdString(hics.at(j).Name);
	QString position= QString::fromStdString(hics.at(j).Position);
    
    
    if (hics.at(j).Name.find("L") != string::npos){
    	
    	const int pos= std::stoi(hics.at(j).Position);
    	//cout<<"pos: "<<pos<<endl;
    	QString partialname=QString::fromStdString(hics.at(j).Name.std::string::substr(6,8));
    	switch (pos){
    	
    	case 1:     		
    	    ui->module_l_1->setPlainText(partialname);
    	    break;
    	case 2:     		
    	    ui->module_l_2->setPlainText(partialname);
    	    break;
    	case 3:     		
    	    ui->module_l_3->setPlainText(partialname);
    	    break;
    	case 4:     		
    	    ui->module_l_4->setPlainText(partialname);
    	    break;
    	case 5:     		
    	    ui->module_l_5->setPlainText(partialname);
    	    break;
    	case 6:     		
    	    ui->module_l_6->setPlainText(partialname);
    	    break;
    	case 7:     		
    	    ui->module_l_7->setPlainText(partialname);
    	    break;
    	
    	default :
    		
    		cout<<"Cannot find modules."<<endl;
    		break;

    	
    	}
    	
    	
    } else if (hics.at(j).Name.find("R") != string::npos){
    	
    	const int pos= std::stoi(hics.at(j).Position);
        	//cout<<"pos: "<<pos<<endl;
        	QString partialname=QString::fromStdString(hics.at(j).Name.std::string::substr(6,8));
        	switch (pos){
        	
        	case 1:     		
        	    ui->module_r_1->setPlainText(partialname);
        	    break;
        	case 2:     		
        	    ui->module_r_2->setPlainText(partialname);
        	    break;
        	case 3:     		
        	    ui->module_r_3->setPlainText(partialname);
        	    break;
        	case 4:     		
        	    ui->module_r_4->setPlainText(partialname);
        	    break;
        	case 5:     		
        	    ui->module_r_5->setPlainText(partialname);
        	    break;
        	case 6:     		
        	    ui->module_r_6->setPlainText(partialname);
        	    break;
        	case 7:     		
        	    ui->module_r_7->setPlainText(partialname);
        	    break;
        	
        	default :
        		
        		cout<<"Cannot find modules."<<endl;
        		break;

        	
        	}
    	
    }
    }
}


//get module parameters for a specific stave
void MainWindow::stave_parameters(string stavename){
	  
	  //string moduleName[14];
	std::vector<string> moduleName;
	moduleName.push_back(ui->module_l_1->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_l_2->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_l_3->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_l_4->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_l_5->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_l_6->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_l_7->toPlainText().toStdString().c_str());
      
	moduleName.push_back(ui->module_r_1->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_r_2->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_r_3->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_r_4->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_r_5->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_r_6->toPlainText().toStdString().c_str());
	moduleName.push_back(ui->module_r_7->toPlainText().toStdString().c_str());	
	
	//cout<<"Size: "<<moduleName.size()<<endl;
	ui->progressBar->setRange(0,moduleName.size());

	std::vector<MStaveR> para_staver;
	int fDatabasetype=0;
    int pixel;
	AlpideDB *theDB = new AlpideDB(fDatabasetype);
    std::string stavenamed;
	for(int i = 0; i<moduleName.size(); i++){
	//para_staver.push_back(this->getStaveRDB(theDB, moduleName[i], 5));
		if (ui->comboBox_option->currentIndex()==0){
			para_staver.push_back(this->getStaveDB(theDB, moduleName[i],4));
			stavenamed=stavename+"_Qualification";
		}else{
			para_staver.push_back(this->getStaveDB(theDB, moduleName[i],5));
			stavenamed=stavename+"_Reception";
		}
	ui->progressBar->setValue(i+1);

	//cout<<i<<" "<<para_staver[i].pixels<<endl;
	
	}
	
	////////plot badpix
	set_plot_style();
	TCanvas *c1 = new TCanvas("Stave","Stave Map",20,10,1000,400);
	c1->Divide(1,2);
	TH2F *pixelsm = new TH2F ("Badpix", "Bad Pixels Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *pixelsh = new TH1F ("Badpix", "Bad Pixels", 200, 0, 50000);

	for(int i=0; i<para_staver.size(); i++){
		pixelsh->Fill(para_staver[i].pixels);  
		if(i>=0 & i<=6){
	      pixelsm->SetBinContent(i+1,1,para_staver[i].pixels);	
		  } else {
		      pixelsm->SetBinContent(i-6,2,para_staver[i].pixels);	
		  } 
	}
	
	
	c1->cd(1);	  
	pixelsm->Draw("COLZ");
	 //gStyle->SetOptStat (kFALSE);
	c1->cd(2);
	pixelsh->Draw();
	
	string name="Bad_Pixels_"+stavenamed+".png";
	const char* cname = name.c_str();
	c1->SaveAs(cname);
	
	////////plot th max
		//set_plot_style();
		TCanvas *c2 = new TCanvas("Stave","Stave Map",20,10,1000,400);
		c2->Divide(1,2);
		TH2F *thmaxm = new TH2F ("THMax", "Maximum chip TH Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
		TH1F *thmaxh = new TH1F ("THMax", "Maximum chip TH", 200, 0, 200);

		for(int i=0; i<para_staver.size(); i++){
			thmaxh->Fill(para_staver[i].ThMax);  
			if(i>=0 & i<=6){
		      thmaxm->SetBinContent(i+1,1,para_staver[i].ThMax);	
			  } else {
			      thmaxm->SetBinContent(i-6,2,para_staver[i].ThMax);	
			  } 
		}
		
		
		c2->cd(1);	  
		thmaxm->Draw("COLZ");
		 //gStyle->SetOptStat (kFALSE);
		c2->cd(2);
		thmaxh->Draw();
		
		string name1="Max_CHIP_TH_"+stavenamed+".png";
		const char* cname1 = name1.c_str();
		c2->SaveAs(cname1);

		////////plot th min
			//set_plot_style();
			TCanvas *c3 = new TCanvas("Stave","Stave Map",20,10,1000,400);
			c3->Divide(1,2);
			TH2F *thminm = new TH2F ("THMin", "Minimum chip TH Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
			TH1F *thminh = new TH1F ("THMin", "Minimum chip TH", 200, 0, 200);

			for(int i=0; i<para_staver.size(); i++){
				thminh->Fill(para_staver[i].ThMin);  
				if(i>=0 & i<=6){
			      thminm->SetBinContent(i+1,1,para_staver[i].ThMin);	
				  } else {
				      thminm->SetBinContent(i-6,2,para_staver[i].ThMin);	
				  } 
			}
			
			
			c3->cd(1);	  
			thminm->Draw("COLZ");
			 //gStyle->SetOptStat (kFALSE);
			c3->cd(2);
			thminh->Draw();
			
			string name2="Min_CHIP_TH_"+stavenamed+".png";
			const char* cname2 = name2.c_str();
			c3->SaveAs(cname2);		
	
	
			
			////////plot noise
						//set_plot_style();
			TCanvas *c4 = new TCanvas("Stave","Stave Map",20,10,1000,400);
			c4->Divide(1,2);
			TH2F *noisem = new TH2F ("Noise", "Noise Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
			TH1F *noiseh = new TH1F ("Noise", "Noise TH", 500, 0, 50);
			
			for(int i=0; i<para_staver.size(); i++){
				noiseh->Fill(para_staver[i].Noise);  
				if(i>=0 & i<=6){
					noisem->SetBinContent(i+1,1,para_staver[i].Noise);	
				} else {
					noisem->SetBinContent(i-6,2,para_staver[i].Noise);	
				} 
			}
			
						
			c4->cd(1);	  
			noisem->Draw("COLZ");
			//gStyle->SetOptStat (kFALSE);
			c4->cd(2);
			noiseh->Draw();
			
			string name3="Noise_"+stavenamed+".png";
			const char* cname3 = name3.c_str();
			c4->SaveAs(cname3);		
			
			////////plot noisy
						//set_plot_style();
			TCanvas *c5 = new TCanvas("Stave","Stave Map",20,10,1000,400);
			c5->Divide(1,2);
			TH2F *noisym = new TH2F ("Noisy", "Noisy Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
			TH1F *noisyh = new TH1F ("Noisy", "Noisy TH", 500, 0, 50);
			
			for(int i=0; i<para_staver.size(); i++){
				noisyh->Fill(para_staver[i].Noisy);  
				if(i>=0 & i<=6){
					noisym->SetBinContent(i+1,1,para_staver[i].Noisy);	
				} else {
					noisym->SetBinContent(i-6,2,para_staver[i].Noisy);	
				} 
			}
			
						
			c5->cd(1);	  
			noisym->Draw("COLZ");
			//gStyle->SetOptStat (kFALSE);
			c5->cd(2);
			noisyh->Draw();
			
			string name4="Noisy_"+stavenamed+".png";
			const char* cname4 = name4.c_str();
			c5->SaveAs(cname4);		

			
			////////plot noisy masked
						//set_plot_style();
			TCanvas *c6 = new TCanvas("Stave","Stave Map",20,10,1000,400);
			c6->Divide(1,2);
			TH2F *noisymm = new TH2F ("Noisy", "Noisy masked Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
			TH1F *noisymh = new TH1F ("Noisy", "Noisy masked TH", 500, 0, 50);
			
			for(int i=0; i<para_staver.size(); i++){
				noisymh->Fill(para_staver[i].NoisyM);  
				if(i>=0 & i<=6){
					noisymm->SetBinContent(i+1,1,para_staver[i].NoisyM);	
				} else {
					noisymm->SetBinContent(i-6,2,para_staver[i].NoisyM);	
				} 
			}
			
						
			c6->cd(1);	  
			noisymm->Draw("COLZ");
			//gStyle->SetOptStat (kFALSE);
			c6->cd(2);
			noisymh->Draw();
			
			string name5="Noisy_Masked_"+stavenamed+".png";
			const char* cname5 = name5.c_str();
			c6->SaveAs(cname5);					
}


void MainWindow::on_draw_clicked(){
	
    string stavename, pic;
	stavename = ui->stave_id->toPlainText().toStdString().c_str();
	
	if (ui->comboBox_option->currentIndex()==0){
		stavename=stavename+"_Qualification";
	}else{
		stavename=stavename+"_Reception";
		}
	
    switch(ui->comboBox_stave->currentIndex()){
    
    case 0:
        pic = "Bad_Pixels_"+stavename+".png";
        break;
    case 1:
        pic = "Max_CHIP_TH_"+stavename+".png";
        break;
    case 2:
    	pic = "Min_CHIP_TH_"+stavename+".png";
    	break;
    case 3:
    	pic = "Noise_"+stavename+".png";
    	break;  
    case 4:
    	pic = "Noisy_"+stavename+".png";
    	break;      	
    case 5:
    	pic = "Noisy_Masked_"+stavename+".png";
    	break;      	
    	
    default:
    	cout<<"error: "<<endl;
    	break;
    
    }

    //pic = "Badpix_"+modulename+".png";
	QString qpic;  
    qpic= QString::fromStdString(pic);

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap(qpic);
    scene->addPixmap(pixmap);
    ui->plot2->setScene(scene);
    ui->plot2->show();
	
}



void MainWindow::set_plot_style()
{
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}





