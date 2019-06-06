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
#include "TMultiGraph.h"

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

ITSDB::ITSDB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ITSDB)
{
    ui->setupUi(this);
}

ITSDB::~ITSDB()
{
    delete ui;
}

//single module button
void ITSDB::on_get_clicked()
{

	string moduleName;
	moduleName = ui->moduleID->toPlainText().toStdString().c_str();
	this->get_module_info(moduleName);

}

void ITSDB::get_module_info(string moduleName){
	
	std::vector<ITSDB::MStaveR> para;
	std::vector<float> index;
	MStaveR para_reception, para_fast, para_HS, para_stave, para_qualification, para_staver;
	int fDatabasetype=0;
      
	AlpideDB *theDB = new AlpideDB(fDatabasetype);
	  
	for(int i=0; i<6; i++){
		para.push_back(this->getStaveRDB(theDB, moduleName,i));
		index.push_back(i);
		  
	}	
	  

	  
	 // this->plot_pixel(para_qualification, para_reception, para_HS, para_stave, para_staver);
	  //this->plot_current(para_qualification,para_reception, para_fast, para_HS, para_stave, para_staver);
	this->addinfo(para);
	this->plot_current(para, index);
	  
	delete theDB;
	
}

//stave info button
void ITSDB::on_get_stave_clicked()
{

	string staveName;

  
	int fDatabasetype=0;
	staveName = ui->stave_id->toPlainText().toStdString().c_str();

	AlpideDB *theDB = new AlpideDB(fDatabasetype);
	this->getstavecompDB(theDB, staveName);

	stave_parameters(staveName);
  
  
	delete theDB;
}



void ITSDB::on_get_module_l1_clicked()
{

	string moduleName=ui->module_l_1->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_1->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_l2_clicked()
{

	string moduleName=ui->module_l_2->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_2->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_l3_clicked()
{

	string moduleName=ui->module_l_3->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_3->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_l4_clicked()
{

	string moduleName=ui->module_l_4->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_4->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_l5_clicked()
{

	string moduleName=ui->module_l_5->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_5->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_l6_clicked()
{

	string moduleName=ui->module_l_6->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_6->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_l7_clicked()
{

	string moduleName=ui->module_l_7->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_l_7->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r1_clicked()
{

	string moduleName=ui->module_r_1->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_1->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r2_clicked()
{

	string moduleName=ui->module_r_2->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_2->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r3_clicked()
{

	string moduleName=ui->module_r_3->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_3->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r4_clicked()
{

	string moduleName=ui->module_r_4->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_4->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r5_clicked()
{

	string moduleName=ui->module_r_5->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_5->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r6_clicked()
{

	string moduleName=ui->module_r_6->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_6->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}

void ITSDB::on_get_module_r7_clicked()
{

	string moduleName=ui->module_r_7->toPlainText().toStdString().c_str();
	QString Qmodulename=ui->module_r_7->toPlainText();
	ui->moduleID->setPlainText(Qmodulename);
	this->get_module_info(moduleName);
	ui->Stave_GUI->setCurrentIndex(1);
  
}


void ITSDB::on_bad_pixels_clicked(){
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


void ITSDB::on_noisy_pixels_clicked(){
	string modulename, pic;
	modulename = ui->moduleID->toPlainText().toStdString().c_str();
    pic = "Noisypix_"+modulename+".png";
	QString qpic;  
    qpic= QString::fromStdString(pic);

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap(qpic);
    scene->addPixmap(pixmap);
    ui->plot1->setScene(scene);
    ui->plot1->show();
		
}

void ITSDB::on_noise_clicked(){
	string modulename, pic;
	modulename = ui->moduleID->toPlainText().toStdString().c_str();
    pic = "Noise_"+modulename+".png";
	QString qpic;  
    qpic= QString::fromStdString(pic);

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap(qpic);
    scene->addPixmap(pixmap);
    ui->plot1->setScene(scene);
    ui->plot1->show();
		
}

void ITSDB::on_current_clicked(){
	
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
//get the HS
//
////////////////////////////////////////////////////////////////////////////////////////////////
void ITSDB::addinfo(std::vector<ITSDB::MStaveR> para)
{
	if (para[0].error!="No activities exit!"){
		ui->info_0->setPlainText("IDDA = "+QString::fromStdString(to_string(para[0].IDDA))+" A");
		ui->info_0->appendPlainText("IDDA clocked = "+QString::fromStdString(to_string(para[0].IDDAC))+" A"); // \n
		ui->info_0->appendPlainText("IDDD = "+QString::fromStdString(to_string(para[0].IDDD))+" A"); // \n
		ui->info_0->appendPlainText("IDDD clocked = "+QString::fromStdString(to_string(para[0].IDDDC))+" A"); // \n
		ui->info_0->appendPlainText("Bad pixels digital (nominal) = "+QString::fromStdString(to_string(para[0].pixels))+" ");
		ui->info_0->appendPlainText("Bad pixels th (0 V) = "+QString::fromStdString(to_string(para[0].pixelsth))+" ");
		ui->info_0->appendPlainText("Maximum chip TH (0 V) = "+QString::fromStdString(to_string(para[0].ThMax))+"e ");
		ui->info_0->appendPlainText("Minimum chip TH (0 V) = "+QString::fromStdString(to_string(para[0].ThMin))+"e ");
		ui->info_0->appendPlainText("Average noise (0 V) = "+QString::fromStdString(to_string(para[0].Noise))+"e ");
		ui->info_0->appendPlainText("Noisy Pixels (0 V) = "+QString::fromStdString(to_string(para[0].Noisy))+" ");
		ui->info_0->appendPlainText("Noisy Pixels masked (0 V) = "+QString::fromStdString(to_string(para[0].NoisyM))+" "); 	  
	}else{
		ui->info_0->setPlainText("No activities exit!");
	}
	if (para[1].error!="No activities exit!"){
		ui->info_1->setPlainText("IDDA = "+QString::fromStdString(to_string(para[1].IDDA))+" A");
		ui->info_1->appendPlainText("IDDA clocked = "+QString::fromStdString(to_string(para[1].IDDAC))+" A"); // \n
		ui->info_1->appendPlainText("IDDD = "+QString::fromStdString(to_string(para[1].IDDD))+" A"); // \n
		ui->info_1->appendPlainText("IDDD clocked = "+QString::fromStdString(to_string(para[1].IDDDC))+" A"); // \n
		ui->info_1->appendPlainText("Bad pixels digital (nominal) = "+QString::fromStdString(to_string(para[1].pixels))+" ");
		ui->info_1->appendPlainText("Bad pixels th (0 V) = "+QString::fromStdString(to_string(para[1].pixelsth))+" ");
		ui->info_1->appendPlainText("Maximum chip TH (0 V) = "+QString::fromStdString(to_string(para[1].ThMax))+"e ");
		ui->info_1->appendPlainText("Minimum chip TH (0 V) = "+QString::fromStdString(to_string(para[1].ThMin))+"e ");
		ui->info_1->appendPlainText("Average noise (0 V) = "+QString::fromStdString(to_string(para[1].Noise))+"e ");
		ui->info_1->appendPlainText("Noisy Pixels (0 V) = "+QString::fromStdString(to_string(para[1].Noisy))+" ");
		ui->info_1->appendPlainText("Noisy Pixels masked (0 V) = "+QString::fromStdString(to_string(para[1].NoisyM))+" "); 	  
	}else{
		ui->info_1->setPlainText("No activities exit!");
	}
	if (para[5].error!="No activities exit!"){
		ui->info_2->setPlainText("IDDA = "+QString::fromStdString(to_string(para[5].IDDA))+" A");
		ui->info_2->appendPlainText("IDDA clocked = "+QString::fromStdString(to_string(para[5].IDDAC))+" A"); // \n
		ui->info_2->appendPlainText("IDDD = "+QString::fromStdString(to_string(para[5].IDDD))+" A"); // \n
		ui->info_2->appendPlainText("IDDD clocked = "+QString::fromStdString(to_string(para[5].IDDDC))+" A"); // \n
  	  
	}else{
		ui->info_2->setPlainText("No activities exit!");
	}
	if (para[2].error!="No activities exit!"){
		ui->info_3->setPlainText("IDDA = "+QString::fromStdString(to_string(para[2].IDDA))+" A");
		ui->info_3->appendPlainText("IDDA clocked = "+QString::fromStdString(to_string(para[2].IDDAC))+" A"); // \n
		ui->info_3->appendPlainText("IDDD = "+QString::fromStdString(to_string(para[2].IDDD))+" A"); // \n
		ui->info_3->appendPlainText("IDDD clocked = "+QString::fromStdString(to_string(para[2].IDDDC))+" A"); // \n
		ui->info_3->appendPlainText("Bad pixels digital (nominal) = "+QString::fromStdString(to_string(para[2].pixels))+" ");
		ui->info_3->appendPlainText("Bad pixels th (0 V) = "+QString::fromStdString(to_string(para[2].pixelsth))+" ");
		ui->info_3->appendPlainText("Maximum chip TH (0 V) = "+QString::fromStdString(to_string(para[2].ThMax))+"e ");
		ui->info_3->appendPlainText("Minimum chip TH (0 V) = "+QString::fromStdString(to_string(para[2].ThMin))+"e ");
		ui->info_3->appendPlainText("Average noise (0 V) = "+QString::fromStdString(to_string(para[2].Noise))+"e ");
		ui->info_3->appendPlainText("Noisy Pixels (0 V) = "+QString::fromStdString(to_string(para[2].Noisy))+" ");
		ui->info_3->appendPlainText("Noisy Pixels masked (0 V) = "+QString::fromStdString(to_string(para[2].NoisyM))+" "); 	  
	}else{
		ui->info_3->setPlainText("No activities exit!");
	}
	if (para[3].error!="No activities exit!"){
		ui->info_4->setPlainText("IDDA = "+QString::fromStdString(to_string(para[3].IDDA))+" A");
		ui->info_4->appendPlainText("IDDA clocked = "+QString::fromStdString(to_string(para[3].IDDAC))+" A"); // \n
		ui->info_4->appendPlainText("IDDD = "+QString::fromStdString(to_string(para[3].IDDD))+" A"); // \n
		ui->info_4->appendPlainText("IDDD clocked = "+QString::fromStdString(to_string(para[3].IDDDC))+" A"); // \n
		ui->info_4->appendPlainText("Bad pixels digital (nominal) = "+QString::fromStdString(to_string(para[3].pixels))+" ");
		ui->info_4->appendPlainText("Bad pixels th (0 V) = "+QString::fromStdString(to_string(para[3].pixelsth))+" ");
		ui->info_4->appendPlainText("Maximum chip TH (0 V) = "+QString::fromStdString(to_string(para[3].ThMax))+"e ");
		ui->info_4->appendPlainText("Minimum chip TH (0 V) = "+QString::fromStdString(to_string(para[3].ThMin))+"e ");
		ui->info_4->appendPlainText("Average noise (0 V) = "+QString::fromStdString(to_string(para[3].Noise))+"e ");
		ui->info_4->appendPlainText("Noisy Pixels (0 V) = "+QString::fromStdString(to_string(para[3].Noisy))+" ");
		ui->info_4->appendPlainText("Noisy Pixels masked (0 V) = "+QString::fromStdString(to_string(para[3].NoisyM))+" "); 	  
	}else{
		ui->info_4->setPlainText("No activities exit!");
	}
	if (para[4].error!="No activities exit!"){
		ui->info_5->setPlainText("IDDA = "+QString::fromStdString(to_string(para[4].IDDA))+" A");
		ui->info_5->appendPlainText("IDDA clocked = "+QString::fromStdString(to_string(para[4].IDDAC))+" A"); // \n
		ui->info_5->appendPlainText("IDDD = "+QString::fromStdString(to_string(para[4].IDDD))+" A"); // \n
		ui->info_5->appendPlainText("IDDD clocked = "+QString::fromStdString(to_string(para[4].IDDDC))+" A"); // \n
		ui->info_5->appendPlainText("Bad pixels digital (nominal) = "+QString::fromStdString(to_string(para[4].pixels))+" ");
		ui->info_5->appendPlainText("Bad pixels th (0 V) = "+QString::fromStdString(to_string(para[4].pixelsth))+" ");
		ui->info_5->appendPlainText("Maximum chip TH (0 V) = "+QString::fromStdString(to_string(para[4].ThMax))+"e ");
		ui->info_5->appendPlainText("Minimum chip TH (0 V) = "+QString::fromStdString(to_string(para[4].ThMin))+"e ");
		ui->info_5->appendPlainText("Average noise (0 V) = "+QString::fromStdString(to_string(para[4].Noise))+"e ");
		ui->info_5->appendPlainText("Noisy Pixels (0 V) = "+QString::fromStdString(to_string(para[4].Noisy))+" ");
		ui->info_5->appendPlainText("Noisy Pixels masked (0 V) = "+QString::fromStdString(to_string(para[4].NoisyM))+" "); 	  
	}else{
		ui->info_5->setPlainText("No activities exit!");
	}
}




struct ITSDB::MStaveR ITSDB::getmodulepara(AlpideDB *theDB, string hicname, const int index){
	
	ActivityDB *theActivityTable = new ActivityDB(theDB);
	MStaveR para;
	int ProjectID = 383;//ITS upgrade project
	int ActivityTypeID=601;
    para.name=hicname;

	switch (index){
	    	
	case 0:     		
		ActivityTypeID=601;
		break;
	case 1:     		
		ActivityTypeID=681;
		break;
	case 2:     		
		ActivityTypeID=881;
		break;
	case 3:     		
		ActivityTypeID=1141;
		break;
	case 4:     		
		ActivityTypeID=1201;
		break;
	case 5:     		
		ActivityTypeID=801;
		break;	    		       	    		
		
	default:
		break;
	}
	vector<ActivityDB::activityShort> *act1 = theActivityTable->GetActivityList(ProjectID, ActivityTypeID);
	  
	unsigned int i=0;
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
struct ITSDB::MStaveR ITSDB::getStaveRDB(AlpideDB *theDB, string hicname, const int index)
{
	QString idda,iddac, iddd,idddc, pixel, pixelth, thmax, thmin, noise, noisy, noisym, error;
	MStaveR para=getmodulepara(theDB, hicname, index);
	return para;
}





void ITSDB::plot_current(std::vector<ITSDB::MStaveR> data, std::vector<float> index){
	
	  //Draw graphs

	
	const int size_p = int(index.size())-1;
	//int size=5;
	float idda[5], iddd[5], iddac[5], idddc[5], pixels[5], pixelsth[5], noisy[5], noisym[5], noise[5];
	float n[5];
	
	for(int i=0; i<size_p; i++){
		
		idda[i]=data[i].IDDA;
		iddd[i]=data[i].IDDD;
		iddac[i]=data[i].IDDAC;
		idddc[i]=data[i].IDDDC;
		pixels[i]=data[i].pixels;
		pixelsth[i]=data[i].pixelsth;
		noisy[i]=data[i].Noisy;
		noisym[i]=data[i].NoisyM;
		noise[i]=data[i].Noise;
		n[i]=index[i]+1;
	 	 }
	  
	TCanvas *c1 = new TCanvas("pixel","pixel",20,10,700,500);
	  
	TMultiGraph *mg = new TMultiGraph();
	   
	//const char* ctitle=("Currents of "+data[0].name).c_str();
	// cout<<ctitle<<endl;
	TGraph* plot = new TGraph(size_p,n, idda);
	  //plot->SetTitle(ctitle);
	TGraph* plot1 = new TGraph(size_p,n, iddd);
	TGraph* plot2 = new TGraph(size_p, n, iddac);
	TGraph* plot3 = new TGraph(size_p, n, idddc);
      
      


	plot->SetMarkerColor(4);
	plot->SetMarkerSize(1);
	plot->SetMarkerStyle(21);
	//plot->SetLineColor(4);
	//plot->SetLineWidth(2);	  
	// plot->Draw();
	plot1->SetMarkerColor(3);
	plot1->SetMarkerSize(1);
	plot1->SetMarkerStyle(21);
	//plot1->SetLineWidth(2); 
	//plot1->Draw("same");
	plot2->SetMarkerColor(2);
	plot2->SetMarkerSize(1);
	plot2->SetMarkerStyle(21);
	//plot2->SetLineWidth(2); 
	//plot2->Draw("P");
	plot3->SetMarkerColor(1);
	plot3->SetMarkerSize(1);
	plot3->SetMarkerStyle(21);
	//plot3->SetLineWidth(2); 
	// plot3->SetTitle(ctitle);
	
	//plot3->Draw("P");
	
	mg->Add(plot);
	mg->Add(plot1);
	mg->Add(plot2);
	mg->Add(plot3);
	mg->Draw("AP");
	mg->SetTitle(("Currents of "+data[0].name).c_str());
	mg->GetYaxis()->SetRangeUser(-0.1,1.3);
	mg->GetXaxis()->SetRangeUser(-0.1,5.9);
	//mg->GetXaxis()->SetTitle("Test ");
	mg->GetYaxis()->SetTitle("I (A)");
	
      
	TText *t = new TText();
	t->SetTextFont(1);
	t->SetTextSize(0.025);
	t->DrawText(0.8, -0.2, "Qualification");
	t->DrawText(1.8, -0.2, "Reception");
	t->DrawText(2.95, -0.2, "HS");
	t->DrawText(3.9, -0.2, "Stave");
	t->DrawText(4.9, -0.2, "StaveR");
	
	  
	auto legend = new TLegend(0.1,0.75,0.3,0.9);
	// legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
	legend->AddEntry(plot,"IDDA configured","P");
	legend->AddEntry(plot1,"IDDD configured","P");
	legend->AddEntry(plot2,"IDDA clocked","P");
	legend->AddEntry(plot3,"IDDD clocked","P");
	legend->Draw();
	
	
	
	//string name="Current_"+data[0].name+".png";
	const char* cname = ("Current_"+data[0].name+".png").c_str();
	c1->SaveAs(cname);
	
	delete plot;
	delete plot1;
	delete plot2;
	delete plot3;

	  //pixels plots
	TCanvas *c2 = new TCanvas("Badpix","Badpix",20,10,700,500);
	TMultiGraph *mg1 = new TMultiGraph();

	TGraph* plot4 = new TGraph(size_p,n, pixels);
	TGraph* plot5 = new TGraph(size_p,n, pixelsth);	  
	plot4->SetMarkerColor(2);
	plot4->SetMarkerSize(1);
	plot4->SetMarkerStyle(21);
	plot5->SetMarkerColor(3);
	plot5->SetMarkerSize(1);
	plot5->SetMarkerStyle(21);
	
	  
	mg1->Add(plot4);
	mg1->Add(plot5);
	mg1->Draw("AP");
	mg1->SetTitle(("Bad pixels of "+data[0].name).c_str());

	mg1->GetXaxis()->SetRangeUser(-0.1,5.9);
	mg1->GetYaxis()->SetRangeUser(pixelsth[0]-1000,pixelsth[0]+1000);
	mg1->GetYaxis()->SetTitle("Pixels");
	
	TText *t1 = new TText();
	t1->SetTextFont(1);
	t1->SetTextSize(0.025);
	t1->DrawText(0.8, pixelsth[0]-1150, "Qualification");
	t1->DrawText(1.8, pixelsth[0]-1150, "Reception");
	t1->DrawText(2.95, pixelsth[0]-1150, "HS");
	t1->DrawText(3.9, pixelsth[0]-1150, "Stave");
	t1->DrawText(4.9, pixelsth[0]-1150, "StaveR");
	
	auto legend1 = new TLegend(0.1,0.75,0.5,0.9);
	// legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
	legend1->AddEntry(plot4,"Bad pixels of digital (nominal)","P");
	legend1->AddEntry(plot5,"Bad pixels of th (0 V)","P");
	
	legend1->Draw();
		
	  //string name="Current_"+data[0].name+".png";
	const char* cname1 = ("Badpix_"+data[0].name+".png").c_str();
	c2->SaveAs(cname1);
	delete plot4;
	delete plot5;
	
	  
	  
	  //hotpix plots
	TCanvas *c3 = new TCanvas("Noisypix","Noisypix",20,10,700,500);
	TMultiGraph *mg2 = new TMultiGraph();

	TGraph* plot6 = new TGraph(size_p,n, noisy);
	TGraph* plot7 = new TGraph(size_p,n, noisym);	  
	plot6->SetMarkerColor(2);
	plot6->SetMarkerSize(1);
	plot6->SetMarkerStyle(21);
	plot7->SetMarkerColor(3);
	plot7->SetMarkerSize(1);
	plot7->SetMarkerStyle(21);
	
	  	  
	mg2->Add(plot6);
	mg2->Add(plot7);
	mg2->Draw("AP");
	mg2->SetTitle(("Noisy pixels of "+data[0].name).c_str());
	
	mg2->GetXaxis()->SetRangeUser(-0.1,5.9);
	mg2->GetYaxis()->SetRangeUser(0,noisy[0]+80);
	mg2->GetYaxis()->SetTitle("Pixels");

	TText *t2 = new TText();
	t2->SetTextFont(1);
	t2->SetTextSize(0.025);
	t2->DrawText(0.8, -(noisy[0]+50)*0.08, "Qualification");
	t2->DrawText(1.8, -(noisy[0]+50)*0.88, "Reception");
	t2->DrawText(2.95, -(noisy[0]+50)*0.08, "HS");
	t2->DrawText(3.9, -(noisy[0]+50)*0.08, "Stave");
	t2->DrawText(4.9, -(noisy[0]+50)*0.08, "StaveR");
	        
	auto legend2 = new TLegend(0.1,0.75,0.5,0.9);
	  	  // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
	legend2->AddEntry(plot6,"Noisy pixels before mask","P");
	legend2->AddEntry(plot7,"Noisy pixels masked","P");
	  	  
	legend2->Draw();
	
	//string name="Current_"+data[0].name+".png";
	const char* cname2 = ("Noisypix_"+data[0].name+".png").c_str();
	c3->SaveAs(cname2);
	delete plot6;
	delete plot7;
	  	  
	  	  	  
	  //noise plots
	TCanvas *c4 = new TCanvas("Noisypix","Noisypix",20,10,700,500);
	TMultiGraph *mg3 = new TMultiGraph();

	TGraph* plot8 = new TGraph(size_p,n, noise);
	//TGraph* plot8 = new TGraph(size_p,n, noisym);	  
	plot8->SetMarkerColor(2);
	plot8->SetMarkerSize(1);
	plot8->SetMarkerStyle(21);
	//plot7->SetMarkerColor(3);
	//plot7->SetMarkerSize(1);
	//plot7->SetMarkerStyle(21);
	
	  	  
	mg3->Add(plot8);
	//mg3->Add(plot7);
	mg3->Draw("AP");
	mg3->SetTitle(("Noise of "+data[0].name).c_str());
	
	mg3->GetXaxis()->SetRangeUser(-0.1,5.9);
	mg3->GetYaxis()->SetRangeUser(0,noise[0]+20);
	mg3->GetYaxis()->SetTitle("e-");

	TText *t3 = new TText();
	t3->SetTextFont(1);
	t3->SetTextSize(0.025);
	t3->DrawText(0.8, -(noise[0]+20)*0.08, "Qualification");
	t3->DrawText(1.8, -(noise[0]+20)*0.88, "Reception");
	t3->DrawText(2.95, -(noise[0]+20)*0.08, "HS");
	t3->DrawText(3.9, -(noise[0]+20)*0.08, "Stave");
	t3->DrawText(4.9, -(noise[0]+20)*0.08, "StaveR");
	        
	auto legend3 = new TLegend(0.1,0.75,0.5,0.9);
	  	  // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
	legend3->AddEntry(plot8,"Noise (0 V)","P");
	//legend2->AddEntry(plot7,"Noisy pixels masked","P");
	  	  
	legend3->Draw();
	
	//string name="Current_"+data[0].name+".png";
	const char* cname3 = ("Noise_"+data[0].name+".png").c_str();
	c4->SaveAs(cname3);
	delete plot8;	  
	  
}



//////////////////////////////////////////////////////////////////////////////////////////

void ITSDB::getstavecompDB(AlpideDB *theDB, string stavename){
	
	std::vector<TChild> halfStaves;
    std::vector<TChild> hics;

	//OL-Stave 519;
	int g_staveType, g_bareStaveType, g_hsUpperType, g_hsLowerType, g_hicType;
	g_staveType     = DbGetComponentTypeId(theDB, "Outer Layer Stave");
	//cout<<"Stave type: "<<g_staveType<<endl;
    g_bareStaveType = DbGetComponentTypeId(theDB, "Outer Layer Stave w/o PB&BB");
    g_hsUpperType   = DbGetComponentTypeId(theDB, "Outer Layer Half-Stave Upper");
    g_hsLowerType   = DbGetComponentTypeId(theDB, "Outer Layer Half-Stave Lower");
    g_hicType = DbGetComponentTypeId(theDB, "Outer Barrel HIC Module");
   // HALFSTAVECOMP   = 8;
    //NHICS           = 14;
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
	DbGetListOfChildren(theDB, stave.Id, staveChildren);
    cout<<"number: "<<staveChildren.size()<<endl;
    
    TChild bareStave;
    
    for (int i = 0; i < int(staveChildren.size()); i++) {
    	if (staveChildren.at(i).Type == g_bareStaveType) {
    		bareStave = staveChildren.at(i);
          //found     = true;
          cout<<"Name:"<<bareStave.Name<<endl;
    		ui->info_stave->appendPlainText("Bare Stave: "+QString::fromStdString(bareStave.Name));
        	}
      	  }

    	std::vector<TChild> bareStaveChildren;
    	DbGetListOfChildren(theDB, bareStave.Id, bareStaveChildren);
	
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
        
    		DbGetListOfChildren(theDB, halfStaves.at(i).Id, halfStaveChildren);

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
void ITSDB::stave_parameters(string stavename){
	  
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
//    int pixel;
	AlpideDB *theDB = new AlpideDB(fDatabasetype);
    std::string stavenamed;
	for(unsigned int i = 0; i<moduleName.size(); i++){
	//para_staver.push_back(this->getStaveRDB(theDB, moduleName[i], 5));
		if (ui->comboBox_option->currentIndex()==0){
			para_staver.push_back(this->getStaveRDB(theDB, moduleName[i],3));
			stavenamed=stavename+"_Qualification";
			}else{
				para_staver.push_back(this->getStaveRDB(theDB, moduleName[i],4));
				stavenamed=stavename+"_Reception";
				}
		ui->progressBar->setValue(i+1);

	//cout<<i<<" "<<para_staver[i].pixels<<endl;
	
	}
	
	////////plot badpix
	set_plot_style();
	TCanvas *c1 = new TCanvas("Stave1","Stave Map",20,10,1000,400);
	c1->Divide(1,2);
	TH2F *pixelsm = new TH2F ("Badpix map", "Bad Pixels Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *pixelsh = new TH1F ("Badpix histo", "Bad Pixels", 200, 0, 50000);

	for(unsigned int i=0; i<para_staver.size(); i++){
		pixelsh->Fill(para_staver[i].pixels);  
		if((i>=0) & (i<=6)){
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
	delete pixelsm;
	delete pixelsh;
	////////plot th max
		//set_plot_style();
	TCanvas *c2 = new TCanvas("Stave2","Stave Map",20,10,1000,400);
	c2->Divide(1,2);
	TH2F *thmaxm = new TH2F ("THMax map", "Maximum chip TH Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *thmaxh = new TH1F ("THMax histo", "Maximum chip TH", 200, 0, 200);

	for(unsigned int i=0; i<para_staver.size(); i++){
		thmaxh->Fill(para_staver[i].ThMax);  
		if((i>=0) & (i<=6)){
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
	delete thmaxm;
	delete thmaxh;
		////////plot th min
			//set_plot_style();
	TCanvas *c3 = new TCanvas("Stave3","Stave Map",20,10,1000,400);
	c3->Divide(1,2);
	TH2F *thminm = new TH2F ("THMin map", "Minimum chip TH Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *thminh = new TH1F ("THMin histo", "Minimum chip TH", 200, 0, 200);
	
	for(unsigned int i=0; i<para_staver.size(); i++){
		thminh->Fill(para_staver[i].ThMin);  
		if((i>=0) & (i<=6)){
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
	delete thminm;
	delete thminh;
	
			
			////////plot noise
						//set_plot_style();
	TCanvas *c4 = new TCanvas("Stave4","Stave Map",20,10,1000,400);
	c4->Divide(1,2);
	TH2F *noisem = new TH2F ("Noise map", "Noise Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *noiseh = new TH1F ("Noise histo", "Noise TH", 500, 0, 50);
	
	for(unsigned int i=0; i<para_staver.size(); i++){
		noiseh->Fill(para_staver[i].Noise);  
		if((i>=0) & (i<=6)){
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
	delete noisem;
	delete noiseh;
			
			////////plot noisy
						//set_plot_style();
	TCanvas *c5 = new TCanvas("Stave5","Stave Map",20,10,1000,400);
	c5->Divide(1,2);
	TH2F *noisym = new TH2F ("Noisy map", "Noisy Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *noisyh = new TH1F ("Noisy histo", "Noisy TH", 500, 0, 50);
	
	for(unsigned int i=0; i<para_staver.size(); i++){
		noisyh->Fill(para_staver[i].Noisy);  
		if((i>=0) & (i<=6)){
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
	delete noisym;
	delete noisyh;
	
	////////plot noisy masked
	//set_plot_style();
	TCanvas *c6 = new TCanvas("Stave6","Stave Map",20,10,1000,400);
	c6->Divide(1,2);
	TH2F *noisymm = new TH2F ("Noisy masked map", "Noisy masked Map", 7, -0.5, 6.5, 2, -0.5, 1.5);
	TH1F *noisymh = new TH1F ("Noisy masked histo", "Noisy masked TH", 500, 0, 50);
	
	for(unsigned int i=0; i<para_staver.size(); i++){
		noisymh->Fill(para_staver[i].NoisyM);  
		if((i>=0) & (i<=6)){
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
	delete noisymm;
	delete noisymh;	
}		


void ITSDB::on_draw_clicked(){
	
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



void ITSDB::set_plot_style()
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





