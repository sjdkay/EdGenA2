      program write_bos
c      use msimsl
      implicit none
      
c ... Include BOS banks
      include 'bcs.inc'

      real*8  moment, moment1
      integer ntrk
      integer ide, idr, id1, id2

c ... BOS bank variables
      character*15  bosfile

      integer  nw, ibid, m0, m8, m1, j2, mevt, run
      integer  ihead, imcev, imcvx, imctk
      integer  nbank, nr
      
      integer  istatus1 
      integer  imchd,ichan_bit_encoded
      integer  id
      
      real*8   q, px, py, pz, E, m, vx, vy, vz
      real*8   x, y, W, Q2, nu
      real*8   rn

      integer event,tot_p,loopp
      integer nevents ! This should be a passed variable, like the bos file name
      nevents = 100
      tot_p = 2
      bosfile= 'ea_vm.bos'

c     ..... Open Bos file (to improve see the gsim_bos.c routine)
c      call fparm(
c     1     'open unit=12 file='//bosfile//'  write recl=32760 '//
c     2     'action=write status=new form=binary')
      call fparm(
     1    "OPEN MCOUT UNIT=2 FILE='bosout.bos' WRITE STATUS=NEW "//
     2    "RECL=32760 SPLITMB=2047 FORM=BINARY")

      
      nw     = 11               ! number of colums in event bank
      ibid   = 2                ! bos output device number
      m0     = 0                ! number of header bank
      m8     = 8                ! number of colums in header bank
      m1     = 1                ! number of rows in header bank
      j2     = 1                ! number of rows in event bank
      mevt   = 1                ! event number
      run    = 10               ! run number for gsim

      call bos(iw,nbcs)
      call bkfmt('HEAD','I')
      call bkfmt('MCTK','(6F,5I)')
      call bkfmt('MCVX','(4F,I)') ! mc vertex parameters
      call blist(iw,'E=','HEAD')
      call blist(iw,'E+','MCVX')
      call blist(iw,'E+','MCTK')
      

c ... Read Input file for specific informations
      open(1,file='output.lund',status='old')
      do event = 1 , nevents
         read(1,*) tot_p        ! Total number of particles
         read(1,*)              ! skip 
         read(1,*)              ! skip
         read(1,*)              ! skip 
         read(1,*)              ! skip
         read(1,*) x            ! skip 
         read(1,*) y            ! skip
         read(1,*) W            ! skip 
         read(1,*) Q2           ! skip
         read(1,*) nu           ! skip

         ihead = nbank('HEAD',0,8,1) ! bos header
         iw(ihead+1)=1
         iw(ihead+2)=run
         iw(ihead+3)=event
         iw(ihead+4)=time()
         iw(ihead+4)=0
         iw(ihead+5)=-2
         iw(ihead+6)=0
         iw(ihead+7)=7
         iw(ihead+8)=1
         
         imcvx = nbank('MCVX',0,5,1)
         imctk = nbank('MCTK',0,11,4)


         do loopp=1, tot_p
            read(1,*)           ! skip            
            read(1,*) q         ! skip
            read(1,*)           ! skip
            read(1,*) id        ! skip
            read(1,*)           ! skip
            read(1,*)           ! skip
            read(1,*) px        ! skip
            read(1,*) py        ! skip
            read(1,*) pz        ! skip
            read(1,*) E         ! skip
            read(1,*) m        ! skip
            read(1,*) vx        ! skip
            read(1,*) vy        ! skip
            read(1,*) vz        ! skip

            if (loopp.eq.1) then
               rw(imcvx+1) = vx
               rw(imcvx+2) = vy
               rw(imcvx+3) = vz
               rw(imcvx+4) = 0.
               iw(imcvx+5) = 0
            endif
            moment = dsqrt(px**2+py**2+pz**2);
            if (moment.eq.0) then 
               moment1 = 1
            else
               moment1 = moment
            endif
               
            rw(imctk+1)=px/moment1 ! Px/P
            rw(imctk+2)=py/moment1 ! Py/P
            rw(imctk+3)=pz/moment1 ! Pz/P
            rw(imctk+4)=moment     ! P
            rw(imctk+5)=m          ! M
            rw(imctk+6)=q          ! Q
            iw(imctk+7)=id         ! ID, e-
            iw(imctk+8)=0          ! flag
            iw(imctk+9)=1          ! beg_vtx   
            iw(imctk+10)=0         ! end_vtx    
            iw(imctk+11)=0         ! parent

            imctk = imctk + 11



         enddo
         call fwbos(iw,ibid,'E',istatus1)
         call bdrop(iw,'E')
         call bgarb(iw)

      enddo
      call fwbos(iw,ibid,'0',istatus1)	
      write(8,*) ' BOS end write status ',istatus1
      call fclos()


      return 
      end
