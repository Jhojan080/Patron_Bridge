#include <iostream>
#include <vector>
using namespace std;


class RemoteControl {
protected:
    Device* device;

public:
    RemoteControl(Device* device) : device(device) {}

    void togglePower() {
        if (device->isEnabled())
            device->disable();
        else
            device->enable();
    }

    void volumeDown() {
        device->setVolume(device->getVolume() - 10);
    }

    void volumeUp() {
        device->setVolume(device->getVolume() + 10);
    }

    void channelDown() {
        device->setChannel(device->getChannel() - 1);
    }

    void channelUp() {
        device->setChannel(device->getChannel() + 1);
    }
};


class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(Device* device) : RemoteControl(device) {}

    void mute() {
        device->setVolume(0);
    }
};


class Device {
public:
    virtual bool isEnabled() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() = 0;
    virtual void setVolume(int percent) = 0;
    virtual int getChannel() = 0;
    virtual void setChannel(int channel) = 0;
};

// Todos los dispositivos siguen la misma interfaz.
class Tv : public Device {
private:
    string brand;
    vector<string> channels;
    int currentChannel;
public:
    Tv(const string& brand, const vector<string>& channels)
        : brand(brand), channels(channels), currentChannel(0) {}

    bool isEnabled() override {
        
        return true;
    }

    void enable() override {
        
        cout << "TV encendida" << endl;
    }

    void disable() override {
        
        cout << "TV apagada" << endl;
    }

    int getVolume() override {
        
        return 50;
    }

    void setVolume(int volumen) override {
        
        cout << "volumen de la TV es: " << volumen << endl;
    }

    int getChannel() override {
        
        return currentChannel;
    }

    void setChannel(int channel) override {
        
        if (channel >= 0 && channel < channels.size()) {
            currentChannel = channel;
            std::cout << "el canal de la TV es " << channels[channel] << endl;
        }
    }
};

class Radio : public Device {
private:

    int volume;
    float channel;

public:
    Radio() : volume(100), channel(100.0f) {}

    bool isEnabled() override {
        
        return true;
    }

    void enable() override {
        
        cout << "La Radio se encendio" << endl;
    }

    void disable() override {
        
        cout << "La Radio se apago" << endl;
    }

    int getVolume() override {
        
        return 30;
    }

    void setVolume(int volumen) override {
        
        cout << "El volumen de la radio es " << volumen << endl;
    }

    int getChannel() override {
        
        return channel;
    }

    void setChannel(float channel)  {
        this->channel = channel;
        cout << "Radio channel set to " << channel << endl;
    }
};

class TvBox : public Device {
private:
    int volumen;
    string currentService;
    string currentMovie;

public:
    TvBox( const vector<string>& channels)
        :volumen(100), currentService("Netflix"), currentMovie("Vengadores") {}

    bool isEnabled() override {
        
        return true;
    }

    void enable() override {
        
        cout << "TV Box encendida" << endl;
    }

    void disable() override {
        
        cout << "TV Box apagada" << endl;
    }

    int getVolume() override {
        
        return volumen;
    }

    void setVolume(int volumen) override {
        
        cout << "Volumen de TV Box" << volumen << endl;
    }

    string getCurrentService() {
        return currentService;
    }

    void setCurrentService(const string& service) {
        currentService = service;
        }

    string getCurrentMovie() {
        return currentMovie;
    }

    void setCurrentMovie(const string& pelicula) {
        currentMovie = pelicula;
    }
};

int main() {
    Tv tv;
    RemoteControl remote(&tv);
    remote.togglePower();
    remote.volumeUp();
    remote.channelUp();

    Radio radio;
    AdvancedRemoteControl advancedRemote(&radio);
    advancedRemote.togglePower();
    advancedRemote.volumeDown();
    advancedRemote.channelDown();
    advancedRemote.mute();

    TvBox tvBox("Xiaomi");

    RemoteControl remote(&tvBox);
    remote.togglePower();
    remote.volumeUp();
    tvBox.setCurrentService("Amazon Prime");
    tvBox.setCurrentMovie("The Matrix");

    return 0;

}