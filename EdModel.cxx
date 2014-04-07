#include "EdModel.h"

EdModel::EdModel(EdInput *inp){

    if( inp ){
      int tot_part = 100;
	length = inp->Get_length();
	len_x = inp->Get_lenx();
	len_y = inp->Get_leny();
	tg_Z = inp->Get_tg_Z();
	tg_N = inp->Get_tg_N();
	energy = inp->Get_eEnergy();
	theta_min = inp->Get_thetaMin();
	theta_max = inp->Get_thetaMax();
	npart = inp->GetNpart();
	tot_part = npart;
	for (int i=0; i<tot_part; i++) pid[i] = inp->GetPid(i);
	nvertex = inp->GetNvertex();
	tot_part = nvertex;
	for (int i=0; i<tot_part; i++) {
	  npvert[i] = inp->GetNpvert(i);
	  overt[i] = inp->GetOvert(i);
	  v_ratio[i] = inp->GetV_ratio(i);
	  v_type[i] = inp->GetV_type(i);
	}
	offset.SetXYZ( inp->GetTgtXoff(),
		       inp->GetTgtYoff(),
		       inp->GetTgtZoff() );

    }

    length = length / 100. ; // conversion distances in m
    len_x = len_x / 100. ; 
    len_y = len_y / 100. ; 
    offset *= 1e-2; // conversion distances in cm to m

    return;
}

EdModel::~EdModel(){
    return;
}
