import subprocess
import tkinter as tk
from tkinter import messagebox
from tkinter import ttk

def calculate_hash():
    input_string = input_entry.get()
    if not input_string:
        messagebox.showerror("Errore", "Inserisci una stringa prima di calcolare l'hash.")
        return

    try:
        result = subprocess.run(['./build/sha_cli'], input=input_string, capture_output=True, text=True, check=True)
        output.delete(1.0, tk.END)
        output.insert(tk.END, result.stdout)
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Errore", f"Errore nell'esecuzione di sha_cli: {e}")
    except FileNotFoundError:
        messagebox.showerror("Errore", "Eseguibile sha_cli non trovato. Assicurati che sia nella cartella ./build/")

# Creazione della finestra principale
root = tk.Tk()
root.title("Calcolatore Hash SHA1")
root.geometry("1000x600")  # Dimensione iniziale della finestra

# Configurazione del layout
root.columnconfigure(0, weight=1)
root.rowconfigure(1, weight=1)

# Frame per l'input
input_frame = ttk.Frame(root, padding="10")
input_frame.grid(row=0, column=0, sticky=(tk.W, tk.E))
input_frame.columnconfigure(1, weight=1)

ttk.Label(input_frame, text="Inserisci una stringa:").grid(row=0, column=0, sticky=tk.W)
input_entry = ttk.Entry(input_frame)
input_entry.grid(row=0, column=1, sticky=(tk.W, tk.E), padx=5)

# Pulsante per calcolare l'hash
calculate_button = ttk.Button(root, text="Calcola Hash", command=calculate_hash)
calculate_button.grid(row=2, column=0, pady=10)

# Area di output
output = tk.Text(root, wrap=tk.WORD)
output.grid(row=1, column=0, sticky=(tk.N, tk.W, tk.E, tk.S), padx=10, pady=10)

# Scrollbar per l'area di output
scrollbar = ttk.Scrollbar(root, orient="vertical", command=output.yview)
scrollbar.grid(row=1, column=1, sticky=(tk.N, tk.S))
output.configure(yscrollcommand=scrollbar.set)

root.mainloop()