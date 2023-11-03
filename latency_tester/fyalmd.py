import serial
import io
import time
import sys
import signal
from subprocess import Popen, PIPE, CalledProcessError
import threading
import numpy as np
import pandas as pd


class FYALMDController:
    def __init__(self, num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder) -> None:
        self.num_measurements = num_measurements
        self.fw_name = fw_name
        self.complexity = complexity
        self.run_fw_test = run_fw_test
        self.program_name = program_name
        self.out_path = f"{out_folder}/{program_name}_{run_fw_test}.csv"
        self.measuring = False
        self.latency_tester_process = None
        self.last_fw_latency = 0
        self.yalmd = serial.Serial('COM6')
        self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester, daemon=True)
        self.measurements = []


    def calibrate_yalmd(self):
        self.yalmd.flushInput()
        time.sleep(5)
        self.yalmd.write('c'.encode())
        yalmd_answer_byte = self.yalmd.readline()
        decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
        print(decoded_answer_bytes)


    def init_fw_latency_tester(self):
        # "D:\Studium\Masterarbeit\mine\latency_tester\cmake-build-debug\latency_tester.exe"
        # D:\Studium\Masterarbeit\mine\FrameworkLatencyTester\test_programs_mine\bitblt
        cmd = [f'D:\Studium\Masterarbeit\mine\FrameworkLatencyTester\latency_tester\{self.program_name}\cmake-build-debug\{self.program_name}.exe']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True, shell=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            if self.measuring == False:
                break
        self.latency_tester_process.kill()


    def start(self):
        self.measuring = True
        self.yalmd.flushInput()
        signal.signal(signal.SIGINT, self.signal_handler)
        if self.run_fw_test:
            self.read_latency_tester_thread.start()
        time.sleep(1)
        

    def stop(self):
        self.measuring = False
        self.yalmd.close()

        if self.run_fw_test:
            self.latency_tester_process.kill()
            #read_latency_tester_thread.join()


    def save_data(self):
        df = pd.DataFrame(self.measurements)
        df.to_csv(self.out_path)

 
    def measure(self):
        self.start()
        while counter < self.num_measurements:
            self.yalmd.write('m'.encode())
            try:
                yalmd_answer_bytes = self.yalmd.readline()
                decoded_answer_bytes = yalmd_answer_bytes[0:len(yalmd_answer_bytes)-2].decode("utf-8")

                ete = int(decoded_answer_bytes)
                diff = (ete - self.last_fw_latency)

                self.measurements.append({'id': counter, 'framework': self.fw_name, 'complexity': self.complexity, 'program': f'{self.program_name}_fw{self.run_fw_test}', 'ete': ete, 'fw': self.last_fw_latency, 'diff': diff})
                counter += 1
            except Exception as e:
                print(e)
                break
        self.stop()



fyalmd_controller = None


def signal_handler(sig, frame):
    if fyalmd_controller:
        fyalmd_controller.stop()
        time.sleep(1)
    sys.exit(0)


if len(sys.argv) == 2:
    if sys.argv[1] == 'calibrate':
        fyalmd_controller = FYALMDController()
        fyalmd_controller.calibrate_yalmd()
        sys.exit(0)

elif len(sys.argv) == 7:
    if sys.argv[1] == 'calibrate_and_measure':
        fyalmd_controller = FYALMDController(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6])
        fyalmd_controller.calibrate_yalmd()
        time.sleep(3)
        fyalmd_controller.measure()
        fyalmd_controller.save_data()
        sys.exit(0)
    elif sys.argv[1] == 'measure':
        fyalmd_controller = FYALMDController(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6])
        fyalmd_controller.measure()
        fyalmd_controller.save_data()
        sys.exit(0)


print('arguments required: action, num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder')
sys.exit(-1)
    