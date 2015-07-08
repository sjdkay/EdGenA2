{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Wed Jul  8 14:39:52 2015) by ROOT version5.34/23
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",264,154,538,323);
   Canvas_1->Range(-40.00001,-16032.84,960,144295.6);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TH1F *htemp__1 = new TH1F("htemp__1","taggedEnergy",100,60,860);
   htemp__1->SetBinContent(8,35038);
   htemp__1->SetBinContent(9,110577);
   htemp__1->SetBinContent(10,78845);
   htemp__1->SetBinContent(11,90975);
   htemp__1->SetBinContent(12,122155);
   htemp__1->SetBinContent(13,80336);
   htemp__1->SetBinContent(14,83823);
   htemp__1->SetBinContent(15,114939);
   htemp__1->SetBinContent(16,76303);
   htemp__1->SetBinContent(17,79830);
   htemp__1->SetBinContent(18,87391);
   htemp__1->SetBinContent(19,53396);
   htemp__1->SetBinContent(20,72344);
   htemp__1->SetBinContent(21,81407);
   htemp__1->SetBinContent(22,47559);
   htemp__1->SetBinContent(23,50422);
   htemp__1->SetBinContent(24,72156);
   htemp__1->SetBinContent(25,23462);
   htemp__1->SetBinContent(26,58186);
   htemp__1->SetBinContent(27,57390);
   htemp__1->SetBinContent(28,72527);
   htemp__1->SetBinContent(29,53241);
   htemp__1->SetBinContent(30,52921);
   htemp__1->SetBinContent(31,75370);
   htemp__1->SetBinContent(32,36813);
   htemp__1->SetBinContent(33,27107);
   htemp__1->SetBinContent(34,45456);
   htemp__1->SetBinContent(35,43351);
   htemp__1->SetBinContent(36,41709);
   htemp__1->SetBinContent(37,47240);
   htemp__1->SetBinContent(38,35360);
   htemp__1->SetBinContent(39,31788);
   htemp__1->SetBinContent(40,50444);
   htemp__1->SetBinContent(41,34991);
   htemp__1->SetBinContent(42,30623);
   htemp__1->SetBinContent(43,37056);
   htemp__1->SetBinContent(44,21446);
   htemp__1->SetBinContent(45,19407);
   htemp__1->SetBinContent(46,30605);
   htemp__1->SetBinContent(47,35748);
   htemp__1->SetBinContent(48,35940);
   htemp__1->SetBinContent(49,30492);
   htemp__1->SetBinContent(50,34565);
   htemp__1->SetBinContent(51,7596);
   htemp__1->SetBinContent(52,30488);
   htemp__1->SetBinContent(53,28076);
   htemp__1->SetBinContent(54,35588);
   htemp__1->SetBinContent(55,19150);
   htemp__1->SetBinContent(56,28095);
   htemp__1->SetBinContent(57,25949);
   htemp__1->SetBinContent(58,33468);
   htemp__1->SetBinContent(59,36436);
   htemp__1->SetBinContent(60,20813);
   htemp__1->SetBinContent(61,31165);
   htemp__1->SetBinContent(62,29592);
   htemp__1->SetBinContent(63,22091);
   htemp__1->SetBinContent(64,27880);
   htemp__1->SetBinContent(65,30658);
   htemp__1->SetBinContent(66,18718);
   htemp__1->SetBinContent(67,18009);
   htemp__1->SetBinContent(68,26415);
   htemp__1->SetBinContent(69,20708);
   htemp__1->SetBinContent(70,15021);
   htemp__1->SetBinContent(71,15600);
   htemp__1->SetBinContent(72,23059);
   htemp__1->SetBinContent(73,20817);
   htemp__1->SetBinContent(74,23354);
   htemp__1->SetBinContent(75,29581);
   htemp__1->SetBinContent(76,24411);
   htemp__1->SetBinContent(77,18520);
   htemp__1->SetBinContent(78,25138);
   htemp__1->SetBinContent(79,20064);
   htemp__1->SetBinContent(80,24674);
   htemp__1->SetBinContent(81,20597);
   htemp__1->SetBinContent(82,22138);
   htemp__1->SetBinContent(83,17901);
   htemp__1->SetBinContent(84,15552);
   htemp__1->SetBinContent(85,15599);
   htemp__1->SetBinContent(86,11893);
   htemp__1->SetBinContent(87,12786);
   htemp__1->SetBinContent(88,11034);
   htemp__1->SetBinContent(89,21225);
   htemp__1->SetBinContent(90,18024);
   htemp__1->SetBinContent(91,7066);
   htemp__1->SetBinContent(92,11258);
   htemp__1->SetEntries(3316941);
   htemp__1->SetDirectory(0);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("htemp");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 3316941");
   text = ptstats->AddText("Mean  =  351.4");
   text = ptstats->AddText("RMS   =    185");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   htemp__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(htemp__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__1->SetLineColor(ci);
   htemp__1->GetXaxis()->SetTitle("taggedEnergy");
   htemp__1->GetXaxis()->SetRange(1,100);
   htemp__1->GetXaxis()->SetLabelFont(42);
   htemp__1->GetXaxis()->SetLabelSize(0.035);
   htemp__1->GetXaxis()->SetTitleSize(0.035);
   htemp__1->GetXaxis()->SetTitleFont(42);
   htemp__1->GetYaxis()->SetLabelFont(42);
   htemp__1->GetYaxis()->SetLabelSize(0.035);
   htemp__1->GetYaxis()->SetTitleSize(0.035);
   htemp__1->GetYaxis()->SetTitleFont(42);
   htemp__1->GetZaxis()->SetLabelFont(42);
   htemp__1->GetZaxis()->SetLabelSize(0.035);
   htemp__1->GetZaxis()->SetTitleSize(0.035);
   htemp__1->GetZaxis()->SetTitleFont(42);
   htemp__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.3898127,0.9348119,0.6101873,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("taggedEnergy");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);

   ofstream myfile;
   myfile.open("energy2.txt");
   for (int i=1; i<100; i++) {
     if (htemp__1->GetBinContent(i)>0) {
       myfile << htemp__1->GetBinLowEdge(i)/1000 << " \t" << (htemp__1->GetBinLowEdge(i) + htemp__1->GetBinWidth(i))/1000 << " \t" << htemp__1->GetBinContent(i) << "\n";    
     }
   }
   myfile.close();

}
