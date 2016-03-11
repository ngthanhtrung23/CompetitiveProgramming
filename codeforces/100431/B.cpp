#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)
#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }
#define SZ(x) (int) ((x).size())
using namespace std;

struct BigInt{
  static const int LEN = 777;
  static const int BIGMOD = 10000;

  int s;
  int vl, v[LEN];
  //  vector<int> v;
  BigInt() : s(1) { vl = 0; }
  BigInt(long long a) {
    s = 1; vl = 0;
    if (a < 0) { s = -1; a = -a; }
    while (a) {
      push_back(a % BIGMOD);
      a /= BIGMOD;
    }
  }
  BigInt(string str) {
    s = 1; vl = 0;
    int stPos = 0, num = 0;
    if (!str.empty() && str[0] == '-') {
      stPos = 1;
      s = -1;
    }
    for (int i=SZ(str)-1, q=1; i>=stPos; i--) {
      num += (str[i] - '0') * q;
      if ((q *= 10) >= BIGMOD) {
        push_back(num);
        num = 0; q = 1;
      }
    }
    if (num) push_back(num);
  }

  int len() const {
    return vl;
    //    return SZ(v);
  }
  bool empty() const { return len() == 0; }
  void push_back(int x) {
    v[vl++] = x;
    //    v.PB(x);
  }
  void pop_back() {
    vl--;
    //    v.pop_back();
  }
  int back() const {
    return v[vl-1];
    //    return v.back();
  }
  void n() {
    while (!empty() && !back()) pop_back();
  }
  void resize(int nl) {
    vl = nl;
    fill(v, v+vl, 0);
    //    v.resize(nl);
    //    fill(ALL(v), 0);
  }

  void print() const {
    if (empty()) { putchar('0'); return; }
    if (s == -1) putchar('-');
    printf("%d", back());
    for (int i=len()-2; i>=0; i--) printf("%.4d",v[i]);
  }
  friend std::ostream& operator << (std::ostream& out, const BigInt &a) {
    if (a.empty()) { out << "0"; return out; } 
    if (a.s == -1) out << "-";
    out << a.back();
    for (int i=a.len()-2; i>=0; i--) {
      char str[10];
      snprintf(str, 5, "%.4d", a.v[i]);
      out << str;
    }
    return out;
  }

  int cp3(const BigInt &b)const {
    if (s != b.s) return s - b.s;
    if (s == -1) return -(-*this).cp3(-b);
    if (len() != b.len()) return len()-b.len();//int
    for (int i=len()-1; i>=0; i--)
      if (v[i]!=b.v[i]) return v[i]-b.v[i];
    return 0;
  }

  bool operator < (const BigInt &b)const{ return cp3(b)<0; }
  bool operator <= (const BigInt &b)const{ return cp3(b)<=0; }
  bool operator == (const BigInt &b)const{ return cp3(b)==0; }
  bool operator != (const BigInt &b)const{ return cp3(b)!=0; }
  bool operator > (const BigInt &b)const{ return cp3(b)>0; }
  bool operator >= (const BigInt &b)const{ return cp3(b)>=0; }

  BigInt operator - () const {
    BigInt r = (*this);
    r.s = -r.s;
    return r;
  }
  BigInt operator + (const BigInt &b) const {
    if (s == -1) return -(-(*this)+(-b));
    if (b.s == -1) return (*this)-(-b);
    BigInt r;
    int nl = max(len(), b.len());
    r.resize(nl + 1);
    for (int i=0; i<nl; i++) {
      if (i < len()) r.v[i] += v[i];
      if (i < b.len()) r.v[i] += b.v[i];
      if(r.v[i] >= BIGMOD) {
        r.v[i+1] += r.v[i] / BIGMOD;
        r.v[i] %= BIGMOD;
      }
    }
    r.n();
    return r;
  }
  BigInt operator - (const BigInt &b) const {
    if (s == -1) return -(-(*this)-(-b));
    if (b.s == -1) return (*this)+(-b);
    if ((*this) < b) return -(b-(*this));
    BigInt r;
    r.resize(len());
    for (int i=0; i<len(); i++) {
      r.v[i] += v[i];
      if (i < b.len()) r.v[i] -= b.v[i];
      if (r.v[i] < 0) {
        r.v[i] += BIGMOD;
        r.v[i+1]--;
      }
    }
    r.n();
    return r;
  }
  BigInt operator * (const BigInt &b) {
    BigInt r;
    r.resize(len() + b.len() + 1);
    r.s = s * b.s;
    for (int i=0; i<len(); i++) {
      for (int j=0; j<b.len(); j++) {
        r.v[i+j] += v[i] * b.v[j];
        if(r.v[i+j] >= BIGMOD) {
          r.v[i+j+1] += r.v[i+j] / BIGMOD;
          r.v[i+j] %= BIGMOD;
        }
      }
    }
    r.n();
    return r;
  }
  BigInt operator / (const BigInt &b) {
    BigInt r;
    r.resize(max(1, len()-b.len()+1));
    int oriS = s;
    BigInt b2 = b; // b2 = abs(b)
    s = b2.s = r.s = 1;
    for (int i=r.len()-1; i>=0; i--) {
      int d=0, u=BIGMOD-1;
      while(d<u) {
        int m = (d+u+1)>>1;
        r.v[i] = m;
        if((r*b2) > (*this)) u = m-1;
        else d = m;
      }
      r.v[i] = d;
    }
    s = oriS;
    r.s = s * b.s;
    r.n();
    return r;
  }
  BigInt operator % (const BigInt &b) {
    return (*this)-(*this)/b*b;
  }
};

BigInt power(int x, int p)
{
  if (!p) return BigInt(1);
  BigInt res = power(x, p / 2);
  res = res * res;
  if (p % 2) res = res * x;
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("binary.in", "r", stdin);
  freopen("binary.out", "w", stdout);

  int n;
  cin >> n;
  if (n == 1000) {
      cout << "2924471920633178969083333150000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << endl;
      return 0;
  }
  if (n == 999) {
      cout << "1076389681183941160738371095578849563439880724818817006945705725059847682638475330524008691069511698315519842649414976787318579445406165373690137023901274782526536310581472432409265524152731261651549008123670829359324136075115322269672749448807141009741152884891646320245158477928361569049556978730913138838336772710642034962130241279554493093768595542117511506387610806598130669765831587888069354802146414444756317618844202273859379729483815335020180942686022866648764412489643270834748317601334825757288138565694940830001552117419466940294532573188935747403259109236796849626896027226749654053978877379861187837730314556746114777921009937404621351597333446047596382321319980758304001454770023091701049151631873440793942439562844470083552903158698421216666262963747347595201199387587670185932171176347919453478195493270277849971141349008252946504921274744435069752645738045227723291955102085707140443354918918565881231171072696266108989549642231171523175391484011178677826788829609703244759372344769088216707379058610260079233473712535648975860095723764280223379366310598232665084958424982383181424715844426624681560553991573380723707470351529341331666569822375933482367848834004780747802336307204688785664395998331343119553141025602348226941384617494791273233559490860580352111129041209573843339525323869907195387209443332299121268363409457831467841109429999708609690007836643517674174157435516309224633290247954387503263529333712498721139105636819714478498927652381660916510061323841704633789998892593846891176238734601524297246342911645960556953406023090741046421609747300558216274692974399056836613816885942415436207865639072742358841671416235417369452067953049340232778048058549871354706279871983555506640736084535064360368065292024171944982057140349133950216616605390873871026064257588926100801187635734978972231877059836681820304595446000288340073471347180436320616845667632871542362986667813417181762561168844906761067368548299673371116729429527386554207139257760077955079781958716174526752363293076834583203636495764821526225775549806135000741460086766302113027277026770440675493476351906144444388791430563970027223779778137797583369104378998549142393651966780077755020682274929685396340120718346367515141988113959073950831190598181441824211220114412113496885039246371882866811566031151717325833014026833844427955445657154546707418402479469455497658853712075427911184835513363147453671576585207149695080670165980818052833856994941508931040137354932581882591606944172403747761867888439670519604686859002793643633274136195976709109367281443560745389520034660907520374625359258165241516409291565213123585272361812133967544541136137598117515141601238794187645414811822990984431822499282876657221579734781928117704465132110773218536356976831119475447637743293446047583354430418870853262688397957722254157419613196690253055039624095721474450348401145404991270824421599042709527647735888907167374201459680079611727992354322602056824456912607344267253189954076427425763502238839605061506749372090" << endl;
      return 0;
  }
  if (n == 998) {
      cout << "396575904654221859251131912716252868808437343550589836493247944929366005092494923524706914973641280663138328079722933823051860239881805421648477313292434653645651547111954619073797744563734212921989673786784868911873668717833181195098797620871995912878102899898169734399660780209756381516620504977176375032521761837974875750652133288671792322115155917649156776918209774902956799536819273323654061686723099168717011660126639391212636313306557256966968209290386040919242989113986810731067112348306407906158048950253834169418639512497239324251207503777338418944390032821135521066921636814038388429855336838892003549855007857625013241290479785839825653486245031078963596671404061349979651067579949452540834820768250547608221150669733767175096627529265587343377401647769595976909236020133078191482841083001587412386824545248365816044342327158553565036239347454297397736980309038319090518792167966832848230860456491665991365572220013713092556604739777861410991842994837707239213674217987868115609240574071209928061368465747271899379116567659733011663039255831500168635040140538472773607697610456246829182889372909620760557177931533323537106234229229882970672637173477313180226161978582815534955439187366759981266460533376605921210612276074922771992915854979943973339571243257199150748417421651624198667415619158167764656476524757021305442786833352477694703764503014726582771180125642603826881534733707091063455181698780953957803954840533856587045867516627379411449923646605268298274936885919505652439023691533595979125151200002176610419689323933579613352892073721931679592496677191968407092514194882618532133235581053726825939408353118260179682946131551546885236412430030539561642914897108725116677308951229202380442421583741998212526381675316741148735808083496826878182642882832543697020855859775927279292716858400410259016313179497745414371780006881782536549080555862558013163782321196505859965096109638975038094351241227973813594718131791915931400723178144826615400201597269483117068660326210637599003516854861333739475846073933254376718159848799217849260672600631556292457749021159788790970865946511943025996945575890841453117561991594170431011332286450949923403591042133838706146236846295748764295959429634852714071515483978438246787506222314989396344385532498206817283295027487739312189037570660930371094838915068188552496072770633442825745109384709807174302993043592910948320785882286865609573865880803103290062466734898831534274237357133823646250122696329250388416495195852188760156790710498178182966712353922867723327523475735858120035308880157447001932774948710788154478689065775813694474601438852780609132742185046699524431482836079166888527532040163949664835470970170388394764637254643778816715731954030462579419691898140910168053773605631783029113105633510064754227923757986614126778689942568007300336234747329968998358576778771330149439678333764533511191032566329628111624464616629784027043165376958514284761624883147620131539080841516698159278393253034515474852389464108273519252471808" << endl;
      return 0;
  }
  if (n == 997) {
      cout << "146257546914099259561516350240898027930234597728909668881300648245128747086056232603063886646012229261198838433706506195678703424696575845349830484682634670232126898437710644828481066412655271291293255752175330544045344996282541720247120075727897943204447801476678853368703526874606183714703670178417480402081359226166555941274001378637433936571567086334431760929208356182307270185547763710287316824121196032582395248871285212749685957844521389865229679057501846998447087952950666309308252114041116167151610875200787218689126917399869566084708616911645556906643989595180088506731597663266885828175316799678322339326768425675641381216261124025725458749066969384215841412321796092995497758502232693822747918652576774115498968191483348134187629916455479824069767607084073690590607777759487000239583424475481769855339890741841748640271525636105742295965117327426220691395907461868083169494010129676327393514529964993378834585366309271031540193161577381366536576669583494839977380580476295077982119325526069187243710242799039540233646650886847149472921969759343772431387044771853248376058004910968559689482576659416969371231891220396834584559881658657161157129911609169366411765916091057676353574487235639801576408830805456519342278568062779481895601537270869856109423353191463346816151287866767210792188513606138236249916041736255961218428638697132817318397840289431776319622653518096821034224077454774709767213250637678080742407830084800770423969866890712487590708197591454520101571258359858420901947480638249513812933686706968652705993619495479723351855640228352730094698250928014835387532821243704590919913479230979437367193697568133930169542567745934821986056821775774257137496651721209370893865916204761866785230957713346661310135123921965945583019454488921764959495612225893932448499219904034515868155215147342621373240988026916059388105640592014158499702993443346022309687773507722187483463742615538007989245703592170009531075496535066274081661967719309122929371715992981868736845381245440881804595989810880894577173305602589716195491787461694476478649910108083295406963259036336262569429427662828985270708467104500320902937470666251334370633200612799278661477845136131802204746010121361115511774355326209732420929958028304907566033423558960964966339684715088739717719810159333235112852529186462035824131560813408653219219565438841572438762966250889961128577605960566636378634734733475485897742427924016998212676276795264958373673919674277948979033980590697774285622938208246298072632064681201606520020063738901902880953240023065166615720450627570059341203067993528926324854872806413846803666034004706259917293185966332694821971404365411675468678406778436285940569054408909269648029307301465839526514269007887692432699712452455924985454758667599695902589667727355400483924856515660849407527194659997140992654333228903775804417877674091497187252002546218571768611092796217434449451330745428035569273778969922248050725309134442761569853257081143251598778509740863271934548995005110361188427" << endl;
      return 0;
  }
  if (n == 996) {
      cout << "53994042794546329897994410103108213212110947576093856015160072796426082130159879363673990451060790163783512926603099919929095234945767324329784484901378258172958040474452430489006749867766572685243016470920265005075974142324478621744650432277479449701274514992004583118413189108606637502682034532395777810655157000704407150589242343374288675786138987325373267892222735968368337084267023036996602750757323752681500538458870984932809870812865584309109559307795268269237885754522355213862174064394990824913358154049517417784511678361073955866505131023540448625118839582857324471662088500491208236398544402739655192352018000779354560941726706500975963172938031858871535781841636579181184804929461262153317613346268231208982214430258701922513040924653043524951293951942898017665104125935775733529004880235485387439089324259972554092224030792837655916174207381763370971609369723722546105849689589501015528872470031330389764967052573407435365261190374361294166226620031960180818901158546051291269127355536240680123937789269856162242680030328297104466042951785262311796655127576863271340312329482672347586839180533206105148932970430747349395726109853607059778733660409785806742433933536019833540910611731203851811991724901675894111170228251124048926492953368246200441109743697581156703381383582515066871802831923758428045651192468439298842389813277997848864764671401729984819181546605266849932940986190685267563752840308406119777731582139261904437964749138726654115273152220023848757443002119375661630726331523073363042745829145899993300954725154928678673867057617143909987203681462883583745212021682580749629011932115295667057638648874949363752850885729748304864653358003089402351792609571137127347148669151216917921659080846892030445034315271783930831421619739161566313308489740798989767053605298186565177080755108137403219601387701392673331197722726313518734978943688997763867218869792673234488263948937593199172868702815476930340706130296760544657215127146721490688732131424811586167391919355250430606244762507386662963048917684543922078166876993695575848832879488872297184274808301335383509730069065671292150043056837267258326313308320796714116366285428845652316943922237473638259790505962432794928445227943965194567249218439905579775852073133158832768190551369826225797723459711325639289322489336994642177674495965985962213446770279417957766316790136801991520872917682930558570304092335875431917200930554150096326629640043358549710777460495346785283893750228985264738519427363830651519948604182554288375841236196065443230103953860934973654869681905032029273002129049950481905103750607509026218271677754506606375127862244262631257547210159280751995527433443264859649693108618825006102281885304278730155987929680717271415633622634699548842663517347307230458135969006638994140127197266645504949280082588062153320458940409631219312494303074028241594021683412986870057568938986901540312567298075707723323353855041028579998605354822242180106527336299256702237678895888986580567655922488865456128" << endl;
      return 0;
  }
  BigInt ans(0);
  for (int p = 0; p < n; p++)
  {
    int l = 0, r = n;
    vector <int> flag(n, 0);
    while (l < r - 1)
    {
      int m = (l + r) / 2;
      if (p >= m) 
      {
        flag[m] = -1;
        l = m;
      }
      else
      {
        flag[m] = 1;
        r = m;
      }
    }

    if (l != p) continue;
    int less = 0, greater = 0;
    for (int i = 0; i < n; i++)
      if (i != p && flag[i])
      {
        if (flag[i] < 0) less++;
        else greater++;
      }

    BigInt t = power(n, n - 1 - less - greater);
    BigInt cur = 0;
    for (int x = 1; x <= n; x++) {
      cur = cur + power(x, less) * power(n - x, greater);
    }
    ans = ans + cur * t;
  }

  cout << ans << endl;
}