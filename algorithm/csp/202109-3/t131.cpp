#define DEBUG
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

double dt;

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
    vector<Pulse> pulses;     // pulses on their way.
    vector<Synapse> synapses; // Synapses from this neuron.

  public:
    Neuron(int rn, double v0, double u0, double a, double b, double c, double d)
        : rn(rn), v(v0), u(u0), a(a), b(b), c(c), d(d) {
        num_pulses_sent = 0;
    }
    void addSynapse(Synapse &syna) { synapses.push_back(syna); }
    void sendPulse(vector<Neuron> &neurons);
    void addPulse(Synapse &syna) { pulses.push_back(syna); }
    void updateStatus(vector<Neuron> &neurons);
    double updatePulses();
    const double getV() const { return v; }
    const int getNumPulsesSent() const { return num_pulses_sent; }
};

double Neuron::updatePulses() {
#ifdef DEBUG
    cout << "    len(pulses)[" << pulses.size() << "]" << endl;
#endif // DEBUG
    double I = 0;
    for (auto iter = pulses.begin(); iter != pulses.end();) {
#ifdef DEBUG
        cout << "    update pulse[" << (iter - pulses.begin()) << "]" << endl;
#endif // DEBUG
        auto &pulse = *iter;
        pulse.update();
#ifdef DEBUG
        cout << "      pulse.countDown[" << pulse.getCountDown() << "]" << endl;
#endif // DEBUG
        if (!pulse.getCountDown()) {
#ifdef DEBUG
            cout << "      pulse arrived. pulse.w[" << pulse.getW() << "]"
                 << endl;
#endif // DEBUG
            I += pulse.getW();
            // iter point to new position of next element.
            iter = pulses.erase(iter);
        } else {
            iter++;
        }
    }

    return I;
}

void Neuron::sendPulse(vector<Neuron> &neurons) {
    for (auto &syna : synapses) {
        auto to = syna.getT();
#ifdef DEBUG
        cout << to << " ";
#endif // DEBUG
        neurons[to].addPulse(syna);
    }
#ifdef DEBUG
    cout << endl;
#endif // DEBUG
}

void Neuron::updateStatus(vector<Neuron> &neurons) {
    double I = updatePulses();
    double vPrev = v, uPrev = u;
    v = vPrev + dt * (0.04 * vPrev * vPrev + 5 * vPrev + 140 - uPrev) + I;
    u = uPrev + dt * a * (b * vPrev - uPrev);
#ifdef DEBUG
    cout << "    v[" << v << "], u[" << u << "], I[" << I << "]" << endl;
#endif // DEBUG

    if (v >= 30) {
#ifdef DEBUG
        cout << "    Send pulses to ";
#endif // DEBUG
       // v_k >= 30, send pulse.
        sendPulse(neurons);
        // Update number of pulses sent
        num_pulses_sent++;
    }
    // v_(k-1)>=30, update v and u after pulse is sent.
    if (v >= 30) {
        v = c;
        u = u + d;
    }
}

class PulseSource {
    int r;
    static unsigned long next;
    vector<Synapse> synapses;

  public:
    PulseSource(int r) : r(r) {}
    int myRand(void);
    void sendPulse(vector<Neuron> &neurons);
    void addSynapse(Synapse &syna) { synapses.push_back(syna); }
};

unsigned long PulseSource::next = 1;

int PulseSource::myRand() {
    next = next * 1103515245 + 12345;
    return ((unsigned)(next / 65536) % 32768);
}

void PulseSource::sendPulse(vector<Neuron> &neurons) {
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
            Pulse pulse(syna);
            neurons[to].addPulse(pulse);
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
#ifdef DEBUG
        cout << "T[" << time << "]:" << endl;
#endif // DEBUG
        for (auto &neu : neurons) {
#ifdef DEBUG
            cout << "  neu[" << &neu - &(*neurons.begin()) << "]: " << endl;
#endif // DEBUG
            neu.updateStatus(neurons);
        }
#ifdef DEBUG
        cout << endl;
#endif // DEBUG
        for (auto &ps : pulseSources) {
#ifdef DEBUG
            cout << "  source[" << &ps - pulseSources.begin().base()
                 << "]:" << endl;
#endif // DEBUG
            ps.sendPulse(neurons);
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
    }

    Simulation sim(N, S, P, T, neurons, pulseSources);
    sim.simulate();
    sim.printAns();

    return 0;
}
