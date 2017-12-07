# Feed angle distance pairs to arduino

import os
import time
from sweeppy import Sweep
from collections import deque
import threading


class Scanner():
    QUEUE_SIZE = 16

    def __init__(self):
        self.queue = deque(maxlen=Scanner.QUEUE_SIZE)
        self.stopThread = False
        self.t = threading.Thread(target=Scanner.run, args=(self,))
        self.t.start()

    def run(self):
        USBTTY_Port = 0
        while not os.path.exists('/dev/ttyUSB%d' % USBTTY_Port):
            USBTTY_Port += 1

        with Sweep('/dev/ttyUSB%d' % USBTTY_Port) as sweep:
            sweep.start_scanning()

            for scan in sweep.get_scans():
                if self.stop.is_set():
                    break
                for s in scan.samples:
                    self.queue.append(s)

    def stop(self):
        self.stop.set()
        self.t.join()





