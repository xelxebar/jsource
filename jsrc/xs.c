/* Copyright 1990-2006, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Xenos: Scripts                                                          */

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#endif

#include "j.h"
#include "x.h"


B jtxsinit(J jt){A x;
 GAT0(x,BOX,10,1); memset(AV(x),C0,AN(x)*SZI); ras(x); jt->slist=x;
 GAT0(x,INT,10,1); memset(AV(x),C0,AN(x)*SZI); ras(x); jt->sclist=x;
 jt->slisti=-1;
 R 1;
}

F1(jtsnl){ASSERTMTV(w); R vec(BOX,jt->slistn,AAV(jt->slist));}
     /* 4!:3  list of script names */

F1(jtscnl){ASSERTMTV(w); R vec(INT,jt->slistn,AAV(jt->sclist));}
     /* 4!:8  list of script indices which loaded slist */


#if (SYS & SYS_MACINTOSH)
void setftype(C*v,OSType type,OSType crea){C p[256];FInfo f;
 __c2p(v,p);
 GetFInfo(p,0,&f);
 f.fdType=type; f.fdCreator=crea;
 SetFInfo(p,0,&f);
}
#endif

/* line/linf arguments:                         */
/* a:   left argument for unlock                */
/* w:   input file or lines; 1 means keyboard   */
/* si:  script index                            */
/* ce:  0 stop on error                         */ 
/*      1 continue on error                     */
/*      2 stop on error or nonunit result       */
/*      3 ditto, but return 0 or 1 result and   */
/*        do not display error                  */
/* tso: echo to stdout                          */

#define SEEKLEAK 0
static A jtline(J jt,A w,I si,C ce,B tso){A x=mtv,z;B xt=jt->tostdout;DC d,xd=jt->dcs;
 if(equ(w,num[1]))R mtm;
 RZ(w=vs(w));
 // Handle locking.  Global glock has lock status for higher levels.  We see if this text is locked; if so, we mark lock status for this level
 // We do not inherit the lock from higher levels, per the original design
 C oldk=jt->uflags.us.cx.cx_c.glock; // incoming lock status
 if((jt->uflags.us.cx.cx_c.glock=(AN(w)&&CFF==*CAV(w)))){
  RZ(w=unlock2(mtm,w));
  ASSERT(CFF!=*CAV(w),EVDOMAIN);
  si=-1; tso=0;  // if locked, keep shtum about internals
 }
 FDEPINC(1);   // No ASSERTs or returns till the FDEPDEC below
 RZ(d=deba(DCSCRIPT,0L,w,(A)si));
 jt->dcs=d; jt->tostdout=tso&&!jt->seclev;
 A *old=jt->tnextpushp;
 switch(ce){
  case 0: while(x&&!jt->jerr){jt->etxn=0;                           immex(x=jgets("   ")); tpop(old);} break;
  case 1: while(x           ){if(!jt->seclev)showerr(); jt->jerr=0; immex(x=jgets("   ")); tpop(old);} break;
  case 2:
  case 3: {
#if SEEKLEAK
    I stbytes = spbytesinuse();
#endif
    while(x&&!jt->jerr){jt->etxn=0;                           immea(x=jgets("   ")); tpop(old);}
    jt->asgn=0;
#if SEEKLEAK
    I endbytes=spbytesinuse(); if(endbytes-stbytes > 1000)printf("%lld bytes lost\n",endbytes-stbytes);
#endif
   }
 }
 jt->dcs=xd; jt->tostdout=xt;
  debz();
 FDEPDEC(1);  // ASSERT OK now
 jt->uflags.us.cx.cx_c.glock=oldk; // pop lock status
 if(3==ce){z=num[jt->jerr==0]; RESETERR; R z;}else RNE(mtm);
}

static F1(jtaddscriptname){I i;
 RE(i=i0(indexof(vec(BOX,jt->slistn,AAV(jt->slist)),box(ravel(w)))));  // look up only in the defined names
 if(jt->slistn==i){
  if(jt->slistn==AN(jt->slist)){RZ(jt->slist=ext(1,jt->slist));RZ(jt->sclist=ext(1,jt->sclist));}
  RZ(ras(w)); RZ(*(jt->slistn+AAV(jt->slist))=w); *(jt->slistn+IAV(jt->sclist))=jt->slisti;
  ++jt->slistn;
 }
 R sc(i);
}



static A jtlinf(J jt,A a,A w,C ce,B tso){A x,y,z;B lk=0;C*s;I i=-1,n,oldi=jt->slisti;
 RZ(a&&w);
 ASSERT(AT(w)&BOX,EVDOMAIN);
 if(jt->seclev){
  y=AAV0(w); n=AN(y); s=CAV(y); 
  ASSERT(LIT&AT(y),EVDOMAIN); 
  ASSERT(3<n&&!memcmp(s+n-3,".js",3L)||4<n&&!memcmp(s+n-4,".ijs",4L),EVSECURE);
 }
 RZ(x=jfread(w));
 // Remove UTF8 BOM if present - commented out pending resolution.  Other BOMs should not occur
 // if(!memcmp(CAV(x),"\357\273\277",3L))RZ(x=drop(num[3],x))
 // if this is a new file, record it in the list of scripts
 RZ(y=fullname(AAV0(w)));
 A scripti; RZ(scripti=jtaddscriptname(jt,y)); i=IAV(scripti)[0];

 // set the current script number
 jt->slisti=(UI4)i;    // glock=0 or 1 is original setting; 2 if this script is locked (so reset after 
 z=line(x,i,ce,tso); 
 jt->slisti=(UI4)oldi;
#if SYS & SYS_PCWIN
 if(lk)memset(AV(x),C0,AN(x));  /* security paranoia */
#endif
 R z;
}

// 4!:6 add script name to list and return its index
F1(jtscriptstring){
 ASSERT(AT(w)&LIT,EVDOMAIN);  // literal
 ASSERT(AR(w)<2,EVRANK);  // list
 R jtaddscriptname(jt,w);   // add name if new; return index to name
}

// 4!:7 set script name to use and return previous value
F1(jtscriptnum){
 I i=i0(w);  // fetch index
 ASSERT(BETWEENO(i,-1,jt->slistn),EVINDEX);  // make sure it's _1 or valid index
 A rv=sc(jt->slisti);  // save the old value
 RZ(rv); jt->slisti=(UI4)i;  // set the new value (if no error)
 R rv;  // return prev value
}

F1(jtscm00 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T+C4T; F1RANK(     r,jtscm00, 0); R r?line(w,-1L,0,0):linf(mark,w,0,0);}
F1(jtscm01 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T+C4T; F1RANK(     r,jtscm01, 0); R r?line(w,-1L,0,1):linf(mark,w,0,1);}
F1(jtscm10 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T+C4T; F1RANK(     r,jtscm10, 0); R r?line(w,-1L,1,0):linf(mark,w,1,0);}
F1(jtscm11 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T+C4T; F1RANK(     r,jtscm11, 0); R r?line(w,-1L,1,1):linf(mark,w,1,1);}
F1(jtsct1  ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T+C4T; F1RANK(     r,jtsct1,  0); R r?line(w,-1L,2,1):linf(mark,w,2,1);}
F1(jtscz1  ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T+C4T; F1RANK(     r,jtscz1,  0); R r?line(w,-1L,3,0):linf(mark,w,3,0);}

F2(jtscm002){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T+C4T; F2RANK(RMAX,r,jtscm002,0); R r?line(w,-1L,0,0):linf(a,   w,0,0);}
F2(jtscm012){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T+C4T; F2RANK(RMAX,r,jtscm012,0); R r?line(w,-1L,0,1):linf(a,   w,0,1);}
F2(jtscm102){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T+C4T; F2RANK(RMAX,r,jtscm102,0); R r?line(w,-1L,1,0):linf(a,   w,1,0);}
F2(jtscm112){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T+C4T; F2RANK(RMAX,r,jtscm112,0); R r?line(w,-1L,1,1):linf(a,   w,1,1);}
F2(jtsct2  ){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T+C4T; F2RANK(RMAX,r,jtsct2,  0); R r?line(w,-1L,2,1):linf(a,   w,2,1);}
F2(jtscz2  ){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T+C4T; F2RANK(RMAX,r,jtscz2,  0); R r?line(w,-1L,3,0):linf(a,   w,3,0);}
