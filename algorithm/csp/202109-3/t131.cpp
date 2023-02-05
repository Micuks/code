// #define DEBUG
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int MAXT = 1e4;
double dt;
int mod = numeric_limits<int>::lowest();

class Synapse {
  protected:
    int s, t;
    double w;
    int D;

  public:
    Synapse(int s, int t, double w, int D) : s(s), t(t), w(w), D(D) {}
    const int getT() const { return t; }
    const int getS() const { return s; }
    const double getW() const { return w; }
    const int getD() const { return D; }
};

class Pulse : public Synapse {
  private:
    int countDown; // Time left before sent out.
  public:
    Pulse(Synapse &syna)
        : Synapse(syna.getS(), syna.getT(), syna.getW(), syna.getD()) {
        countDown = syna.getD();
    }
    const int getCountDown() const { return countDown; }
    void update() { countDown--; }
};

class Neuron {
    int rn; // Number of this kind of neuron.
    double v, u, a, b, c, d;
    int num_pulses_sent;
    double I[MAXT];
    vector<Synapse> synapses; // Synapses from this neuron.

  public:
    Neuron(int rn, double v0, double u0, double a, double b, double c, double d)
        : rn(rn), v(v0), u(u0), a(a), b(b), c(c), d(d) {
        num_pulses_sent = 0;
        memset(I, 0, MAXT * sizeof(double));
    }
    void addSynapse(Synapse &syna) { synapses.push_back(syna); }
    void sendPulse(const int time, vector<Neuron> &neurons);
    void addPulse(const int time, const int d, const double w);
    void updateStatus(const int time, vector<Neuron> &neurons);
    const double getV() const { return v; }
    const int getNumPulsesSent() const { return num_pulses_sent; }
};

void Neuron::addPulse(const int time, const int d, const double w) {
    I[(time + d) % mod] += w;
}

void Neuron::sendPulse(const int time, vector<Neuron> &neurons) {
    for (auto &syna : synapses) {
        auto to = syna.getT();
#ifdef DEBUG
        cout << to << " ";
#endif // DEBUG
        neurons[to].addPulse(time, syna.getD(), syna.getW());
    }
#ifdef DEBUG
    cout << endl;
#endif // DEBUG
}

void Neuron::updateStatus(const int time, vector<Neuron> &neurons) {
    double currI = I[time];
    double vPrev = v, uPrev = u;
    v = vPrev + dt * (0.04 * vPrev * vPrev + 5 * vPrev + 140 - uPrev) + currI;
    u = uPrev + dt * a * (b * vPrev - uPrev);
#ifdef DEBUG
    cout << "    v[" << v << "], u[" << u << "], I[" << currI << "]" << endl;
#endif // DEBUG

    if (v >= 30) {
#ifdef DEBUG
        cout << "    Send pulses to ";
#endif // DEBUG
       // v_k >= 30, send pulse.
        sendPulse(time, neurons);
        // Update number of pulses sent
        num_pulses_sent++;
    }
    // v_(k-1)>=30, update v and u after pulse is sent.
    if (v >= 30) {
        v = c;
        u = u + d;
    }

    I[time] = 0;
}

class PulseSource {
    int r;
    static unsigned long next;
    vector<Synapse> synapses;

  public:
    PulseSource(int r) : r(r) {}
    int myRand(void);
    void sendPulse(const int time, vector<Neuron> &neurons);
    void addSynapse(Synapse &syna) { synapses.push_back(syna); }
};

unsigned long PulseSource::next = 1;

int PulseSource::myRand() {
    next = next * 1103515245 + 12345;
    return ((unsigned)(next / 65536) % 32768);
}

void PulseSource::sendPulse(const int time, vector<Neuron> &neurons) {
    int rand = myRand();
#ifdef DEBUG
    cout << "    r[" << r << "], "
         << "rand[" << rand << "] " << endl;
#endif // DEBUG

    if (r > rand) {
#ifdef DEBUG
        cout << "    send pulses to ";
#endif // DEBUG
       // Send Pulse
        for (auto &syna : synapses) {
            auto to = syna.getT();
#ifdef DEBUG
            cout << to << " ";
#endif // DEBUG
            neurons[to].addPulse(time, syna.getD(), syna.getW());
        }
#ifdef DEBUG
        cout << endl;
#endif // DEBUG
    }
}

class Simulation {
    int N, S, P, T;
    vector<Neuron> neurons;
    vector<PulseSource> pulseSources;
    double maxV, minV;
    int maxPulses, minPulses;

  public:
    Simulation(int N, int S, int P, int T, vector<Neuron> &neurons,
               vector<PulseSource> &pulseSources)
        : N(N), S(S), P(P), T(T), neurons(neurons), pulseSources(pulseSources) {
    }
    void simulate();
    void printAns();
};

void Simulation::simulate() {
    for (int time = 1; time <= T; time++) {
        int modTime = time % mod;
#ifdef DEBUG
        cout << "T[" << time << "], modT[" << modTime << "]:" << endl;
#endif // DEBUG
        for (auto &ps : pulseSources) {
#ifdef DEBUG
            cout << "  source[" << &ps - pulseSources.begin().base()
                 << "]:" << endl;
#endif // DEBUG
            ps.sendPulse(modTime, neurons);
        }
        for (auto &neu : neurons) {
#ifdef DEBUG
            cout << "  neu[" << &neu - &(*neurons.begin()) << "]: " << endl;
#endif // DEBUG
            neu.updateStatus(modTime, neurons);
        }
    }
}

void Simulation::printAns() {
    maxV = numeric_limits<double>::lowest();
    minV = numeric_limits<double>::max();
    maxPulses = numeric_limits<int>::lowest();
    minPulses = numeric_limits<int>::max();
    for (const auto &neu : neurons) {
        maxV = max(maxV, neu.getV());
        minV = min(minV, neu.getV());
        maxPulses = max(maxPulses, neu.getNumPulsesSent());
        minPulses = min(minPulses, neu.getNumPulsesSent());
    }
    cout << setprecision(3) << fixed;
    cout << minV << " " << maxV << endl;
    cout << minPulses << " " << maxPulses << endl;
}

int main() {
    mod = numeric_limits<int>::lowest();
    int N, S, P, T;
    cin >> N >> S >> P >> T;
    cin >> dt;
#ifdef DEBUG
    cout << N << " " << S << " " << P << " " << T << endl;
    cout << dt << endl;
#endif // DEBUG

    // Read neurons.
    vector<Neuron> neurons;
    int sum_rns = 0;
    while (sum_rns < N) {
        int rn;
        double v0, u0, a, b, c, d;
        cin >> rn >> v0 >> u0 >> a >> b >> c >> d;
#ifdef DEBUG
        cout << rn << " " << v0 << " " << u0 << " " << a << " " << b << " " << c
             << " " << d << endl;
#endif // DEBUG

        Neuron neu(rn, v0, u0, a, b, c, d);
        for (int i = 0; i < rn; i++) {
            neurons.push_back(neu);
        }

        sum_rns += rn;
    }

    // Read Pulse sources.
    vector<PulseSource> pulseSources;
    for (int i = 0; i < P; i++) {
        int r;
        cin >> r;
#ifdef DEBUG
        cout << r << " ";
#endif // DEBUG
        PulseSource pr(r);
        pulseSources.push_back(pr);
    }
#ifdef DEBUG
    cout << endl;
#endif // DEBUG

    // Read Synapses.
    for (int i = 0; i < S; i++) {
        int _s, _t, _d;
        double _w;
        cin >> _s >> _t >> _w >> _d;
#ifdef DEBUG
        cout << _s << " " << _t << " " << _w << " " << _d << endl;
#endif // DEBUG
        if (_s >= N) {
            // This synapse is from pulse source.
            _s -= N;
            Synapse syna(_s, _t, _w, _d);
            pulseSources[_s].addSynapse(syna);
        } else {
            // This synapse is from neuron.
            Synapse syna(_s, _t, _w, _d);
            neurons[_s].addSynapse(syna);
        }
        mod = max(mod, _d + 1);
    }

    Simulation sim(N, S, P, T, neurons, pulseSources);
    sim.simulate();
    sim.printAns();

    return 0;
}
