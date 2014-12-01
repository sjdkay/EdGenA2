#include "EdPhysics.h"


#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "TRandom.h"




EdPhysics::EdPhysics(EdModel *model){
  
    pdg = new TDatabasePDG();
    pdg->ReadPDGTable("eg_pdg_table.txt");
    fRandom = new TRandom2(0);
    printf("Seed number %d\n",fRandom->GetSeed());
    target.SetPxPyPzE(0.0, 0.0, 0.0, model->Get_tgMass()); // target at rest
 
    n_part = model->GetNpart();
    nvertex = model->GetNvertex();
    part_pdg[n_part] = pdg->GetParticle(model->GetBeamPID()); // Beam particle stored in part_pdg[n_part]
    double masses2[n_part];
    for (int i=0; i<n_part; i++) {
      towrite[i] = 1;
      particle_id[i] = model->GetPid(i);
      part_pdg[i] = pdg->GetParticle(particle_id[i]); 
      charge[i] = part_pdg[i]->Charge()/3; // Charge is in unit of |e|/3
      masses2[i] = part_pdg[i]->Mass();
      printf("Particle n.%i \t pid=%i \t mass=%.3e GeV \n",i+1,particle_id[i],masses2[i]);
    }
    nvertex = model->GetNvertex();
    int atpart = 0;
    for (int i=0; i<nvertex; i++) {
      overt[i] = model->GetOvert(i);
      if (overt[i] > 0) towrite[overt[i]-1] = 0; // Setting not to write particle already decayed in the LUND or BOS file
      npvert[i] = model->GetNpvert(i);
      v_type[i] = model->GetV_type(i);
      v_ratio[i] = model->GetV_ratio(i);
      if (overt[i] == 0) printf("Vertex n. %i, Origin (Beam + Tg) --> ",i+1);
      else printf("Vertex n. %i, Origin (pid=%i %.3e GeV,  Lifetime=%.3e) --> ",i+1,particle_id[overt[i]-1],part_pdg[overt[i]-1]->Mass(),part_pdg[overt[i]-1]->Lifetime());
      for(int j=0; j<npvert[i] ; j++) {
	masses[i][j] = part_pdg[atpart]->Mass();
	printf("(pid=%i %.3e GeV) ", particle_id[atpart], part_pdg[atpart]->Mass());
	atpart++;
	if (j==(npvert[i]-1)) printf(" \n");
	else printf(" + ");
      }
    }
    
 

 
 
    return;
}

EdPhysics::~EdPhysics(){
    return;
}

void EdPhysics::MakeEvent(EdOutput *out , EdModel *model){
  // target info

    double  e_lab = model->GetEnergy();
    out->SetEin(e_lab);
    beam.SetPxPyPzE(0.0, 0.0,e_lab,e_lab);
    double tglx = model->GetLx();
    double tgly = model->GetLy();
    double tglength = model->GetLength();

    TVector3 tgtoff = model->GetTgtOffset();


    double theta_min = model->GetTheta_min();
    double theta_max = model->GetTheta_max();
  

    nucl n;
    double A = ((double) (model->Get_tgZ()+model->Get_tgN()));
    double prot_prob = ((double) model->Get_tgZ())/A;
    // Determine which type of nucleon we hit
    if( fRandom->Uniform() < prot_prob ){
	n = kProton;
    } else {
	n = kNeutron;
    }    

    TLorentzVector *p4vector[n_part+1];
    //    for (int i=0; i<(n_part+1) ; i++) p4vector[i]->SetPxPyPzE(0.,0.,0.,0.);
    TLorentzVector W4vector(0.,0.,0.,0.);
    TLorentzVector Q4vector(0.,0.,0.,0.);

    double pos_x = GetBeamProfile(tglx);
    double pos_y = GetBeamProfile(tgly);
    double pos_z = fRandom->Uniform(-0.5*tglength,0.5*tglength);
    TVector3 vertex(pos_x,pos_y,pos_z);
    double weight2;
    vertex = vertex + tgtoff;
    int atpart = 0;
    for (int i=0; i<nvertex; i++) {
      if (overt[i] == 0) { // (Origin Beam + Tg)
	Wtg = beam + target;
      }
      else {
	Wtg = *p4vector[overt[i]-1];
      }
      SetDecay(Wtg, npvert[i], masses[i]);
      weight2 = Generate();
      for (int j=0; j<npvert[i]; j++) {
	p4vector[atpart] = GetDecay(j);
	//	cout << "Particle n." << atpart << " Mass=" << p4vector[atpart]->M() << endl; 
	theta[atpart] = p4vector[atpart]->Theta();
	phi[atpart] = p4vector[atpart]->Phi();
	Ef[atpart] = p4vector[atpart]->E();
	pf[atpart] = p4vector[atpart]->Rho();
	px[atpart] = p4vector[atpart]->Px();
	py[atpart] = p4vector[atpart]->Py();
	pz[atpart] = p4vector[atpart]->Pz();
	if (atpart<npvert[0] && atpart>0) W4vector += *p4vector[atpart]; // I am assuming that the first particle is the scattered beam
	if (atpart == 0)      Q4vector= beam - *p4vector[0];
	weight[atpart] = weight2;
	if (overt[i] ==0) {
	  vx[atpart] = vertex.X();
	  vy[atpart] = vertex.Y();
	  vz[atpart] = vertex.Z();
	}
	else {
	  if (part_pdg[overt[i]-1]->Stable() == 1) {
	    printf("Origin particle %i at vertex %i is stable??? vertexes of daughters particles as mother \n", particle_id[overt[i]-1],i); 
	    vx[atpart] = vx[overt[i]-1];
	    vy[atpart] = vy[overt[i]-1];
	    vz[atpart] = vz[overt[i]-1];
	  }
	  else {
	    vertex.SetXYZ(vx[overt[i]-1],vy[overt[i]-1],vz[overt[i]-1]);
	    vertex = Decay_vertex(p4vector[overt[i]-1],(overt[i]-1),vertex);
	    vx[atpart] = vertex.X() ;
	    vy[atpart] = vertex.Y();
	    vz[atpart] = vertex.Z();
	  }

	  
	}
	atpart++;
      } 
    }
    

     out->SetTheta(theta,n_part);
     out->SetPhi(phi,n_part);
     out->SetEf(Ef,n_part);
     out->Setpf(pf,n_part);
     out->Setpx(px,n_part);
     out->Setpy(py,n_part);
     out->Setpz(pz,n_part);
     out->Setparticle_id(particle_id,n_part);
     out->Setcharge(charge,n_part);
     out->Setweight(weight,n_part);
     out->Settowrite(towrite,n_part);
    
    // Here I need to fix the energy, because I do not know the kinematics at now and I generate randomly the momentum.
    
  
    Z_ion = model->Get_tgZ(); 
    N_ion = model->Get_tgN();
    W = W4vector.M();
    Q2= -Q4vector.M2(); 
    nu= Q4vector.Dot(target)/target.M(); 
    x = Q2/(2*target.M()*nu);
    y = Q4vector.Dot(target)/beam.Dot(target);

    out->SetZ_ion(Z_ion);
    out->SetN_ion(N_ion);
    out->Setx(x);
    out->Sety(y);
    out->SetW(W);
    out->SetQ2(Q2);
    out->Setnu(nu);
    out->Setvx(vx,n_part);
    out->Setvy(vy,n_part);
    out->Setvz(vz,n_part);
 

    
    out->Write();

    return;
}



double EdPhysics::GetBeamProfile( double sigma){
  return fRandom->Gaus(0.,sigma);
}




TVector3 EdPhysics::Decay_vertex(TLorentzVector *Vp_4, int i, TVector3 vert) {

  TVector3 b_3 ; // beta to boost the LAB frame for going in the pi0 rest frame 
  b_3 = Vp_4->BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

  double lifetime = part_pdg[i]->Lifetime();
  TLorentzVector test(0.,0.,0.,lifetime);
  TVector3 result;
  test.Boost(b_3);
  if (test.Rho() < 1e-20) result = vert;
  else {
    double toptime = lifetime * 20; // exp(-20) = 2.0e-9
    //define vertex of the decayed particles...
    TF1 *fr = new TF1("fr","exp(-x/([0]))",0,toptime) ; // 8.4e-17 is the mean lifetime of the pi0
    fr->SetParameter(0,lifetime);
    double time = fr->GetRandom(0.,toptime);
    TLorentzVector move(0.,0.,0.,time); // displacement for the creation of the two gammas in the pi0 rest frame
    move.Boost(b_3); // displacement for the creation of the two gammas in the LAB frame
 
    result.SetX( vert.X() + move.X() );
    result.SetY( vert.Y() + move.Y() );
    result.SetZ( vert.Z() + move.Z() );

    delete fr;
  }

  return result;

}



// double EdPhysics::t_reaction(TLorentzVector *Vrecoil_tg_4 ) {
//   TLorentzVector tg_v4;
//   tg_v4.SetPxPyPzE(Vrecoil_tg_4->Px(),Vrecoil_tg_4->Py(),Vrecoil_tg_4->Pz(),Vrecoil_tg_4->E());
//   TLorentzVector t_v4;
//   t_v4 = target - tg_v4; // Operation allowed just between TLorentzVector and not TLorentzVector*
//   return t_v4.M2();

// }


// Double_t TPart_ident_ct::theta_pip_mc() {

//   p_theta_pip_mc = 0;

//   TVector3 V3_e, V3_e2;
//   TVector3 V3_1 , V3_2 , V3_3, V3_4;

//   V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
//   V3_e2.SetXYZ(px_mc(11),py_mc(11),pz_mc(11)); // Scattered electron  
//   V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
//   V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
//   V3_4 = ( V3_e - V3_e2 ) - ( V3_1 + V3_2) ; // outgoing proton
//      // 3-momentum = - t =
//      // gamma* - rho0

//   TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
//   TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
//   TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum


//   TLorentzVector V4_3 ; // rho momentum
//   V4_3 = V4_1 + V4_2; 
//   V3_3 = V3_1 + V3_2;

//   TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
//  // rest frame 

//   b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

//   b_3 = - b_3; // the Boost function in TLorentzVector is an anti-lorentz transform 

//   V4_4.Boost(b_3); // proton in the rho0 frame

//   V4_2.Boost(b_3); // pi+ in the rho0 frame

//   V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
//        // the rho0 frame
//   V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
//        // the rho0 frame
  
//   p_theta_pip_mc = TMath::Pi() - V3_2.Angle(V3_4) ;  // angle between
//      // the opposite 
//      // of the
//      // direction of
//      // the proton and
//      // the pi+
  
//   return p_theta_pip_mc;
  
  
  


// }

// //-----------------------------------------
// double EdPhysics::phi_lep_had(TLorentzVector *Vrecoil_tg_4, TLorentzVector *Velectron_4, TLorentzVector *Vmeson_4, double e_lab) {

// //   // 11 = electron , -211 = pi- , 211 = pi+

//   double phi_lep_had_v = 0;

//   TVector3 V3_1 , V3_2 ,V3_3 ,V3_6;
//   V3_1 = Velectron_4->Vect(); // e' momentum
//   V3_2.SetXYZ(0,0,e_lab); // e momentum
//   V3_3 = V3_2 - V3_1;   // Virtual photon momentum vector
//   V3_6 = Vmeson_4->Vect(); // rho0 momentum


//   TVector3 n_lep, n_had;

//   n_lep = V3_2.Cross(V3_1);

//   n_had = V3_3.Cross(V3_6);

  
//   phi_lep_had_v = n_lep.Angle(n_had);

//   return phi_lep_had_v;

// }


// double EdPhysics::phi_pip_mc() {

//    p_phi_pip_mc = 0;
  
//   TVector3 V3_e, V3_e2, V3_g;
//   TVector3 V3_1 , V3_2 , V3_3, V3_4;

//   V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
//   V3_e2.SetXYZ(px_mc(11),py_mc(11),pz_mc(11)); // Scattered electron  
//   V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
//   V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
//   V3_4 = ( V3_e - V3_e2 ) - ( V3_1 + V3_2) ; // outgoing proton
//      // 3-momentum = - t =
//      // gamma* - rho0
//   V3_g = V3_e - V3_e2;  // gamma* momentum

//   TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
//   TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
//   TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum


//   TLorentzVector V4_3 ; // rho momentum
//   V4_3 = V4_1 + V4_2; 
//   V3_3 = V3_1 + V3_2;


//   TVector3 n_had, n_z, n_x , opip;

//   n_had = V3_g.Cross(V3_3);  // p_gamma* X p_rho    : is parallel to
//      //                       the y axis and
//      //                       is perpendicular
//      //                       to the boost
//                              // it is let unchanged from the boost

//   n_had = n_had.Unit();      // creatin the unit vector in the
//      // y direction 

//   TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
//  // rest frame 

//   b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

//   b_3 = - b_3;

//   V4_4.Boost(b_3); // proton in the rho0 frame

//   V4_2.Boost(b_3); // pi+ in the rho0 frame

//   V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
//        // the rho0 frame
//   V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
//        // the rho0 frame
  
//   n_z = - V3_4.Unit();  // z axis is opposite to the outgoing proton
//   n_x = n_had.Cross(n_z); // x axis = (y axis) X (z axis)  

//   opip = n_z.Cross(V3_2);

//   Double_t sen_phi_ev = asin( - n_x.Dot(opip) / opip.Mag());

//   p_phi_pip_mc = acos(n_had.Dot(opip) / opip.Mag()); // this angle is
//      // defined from 0
//      // to 2 Pi
//   if (sen_phi_ev < 0 ) {
//     p_phi_pip_mc = 2 * TMath::Pi() - p_phi_pip_mc ;  // if sen (phi)<0
//      // phi= 2Pi - phi
     
//   }
   
  
//   return p_phi_pip_mc;
  
  


// }
