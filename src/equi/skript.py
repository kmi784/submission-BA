
import subprocess

target = "L120-U"
Tmin, Tmax = 0.3, 0.34

Njack = 100
precession = 0.000001

def execute(command :str) :
    print(command)
    subprocess.run(command, shell=True, cwd="../data/kalz")

execute("time ./mean " + target + " " + target + "/mean.txt")

execute("time ./wham " + target + " " + target + "/wham.txt " + str(Tmin) + " " + str(Tmax) + " 400")

execute("time ./peak " + target + " " + "fit.txt " + str(Njack) + " " + str(Tmin) + " " + str(Tmax) + " " + str(int((Tmax-Tmin)/precession)))

