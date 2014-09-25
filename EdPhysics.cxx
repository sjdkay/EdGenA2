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
    
  
    Z_ion = 2;
    N_ion = 2;
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




