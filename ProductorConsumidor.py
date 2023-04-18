#!/usr/bin/env python3
import threading
import time

# tamaño del búfer
BUFFER_SIZE = 5
# búfer compartido
buffer = []

buffer_lock = threading.Lock()
# variable condicional para señalizar si el búfer está lleno o vacío
buffer_empty = threading.Condition()
buffer_full = threading.Condition()

class Producer(threading.Thread):
    def run(self):
        global buffer
        while True:
            # producir un nuevo elemento
            item = time.time()
            with buffer_full:
                #mutex1.acquire()
                while len(buffer) == BUFFER_SIZE:
                    buffer_full.wait()
                # añadir el elemento al búfer
                with buffer_lock:
                    buffer.append(item)
                print(f'Produced {item}')
                with buffer_empty:
                    buffer_empty.notify()
                    #mutex1.release()
                

class Consumer(threading.Thread):
    def run(self):
        global buffer
        while True:
            with buffer_empty:
               # mutex2.acquire()
                while len(buffer) == 0:
                    buffer_empty.wait()
                # consumir un elemento del búfer
                with buffer_lock:
                    item = buffer.pop(0)
                print(f'Consumed {item}')
                with buffer_full:
                    buffer_full.notify()
               
# crear productores y consumidores
threads = []
for i in range(2):
    threads.append(Producer())
for i in range(2):
    threads.append(Consumer())

# iniciar hilos
for t in threads:
    t.start()

# esperar a que todos los hilos terminen
for t in threads:
    t.join()

