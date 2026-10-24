# Deep Learning I: Practical Work
> Lab notebooks and course notes from the **Deep Learning I** course

The repository gathers:
- **`TPs/`:** the practical sessions, completed in Python (NumPy, PyTorch, Keras, PyTorch Lightning)
- **`Lesson_Recap.pdf`:** my course summary (MLP, CNN, RNN/LSTM/GRU, Transformers): the theory behind every model used here lives there, this README only describes what was done in the labs

> The lab subjects were given to me and my job was to complete them: the `# START CODE HERE` / `# STUDENT CODE` parts are my implementation.

---

## Overview
| Lab | Topic | Task | Data | Framework |
|---|---|---|---|---|
| **TP1** | MLP | Binary classification, from scratch then in PyTorch | `make_circles` (sklearn) | NumPy, PyTorch |
| **TP2.1** | CNN | Image classification | MNIST, CIFAR-10 | PyTorch |
| **TP2.2** | CNN | Deep Dream & adversarial examples | ImageNet images | PyTorch, pre-trained VGG19 |
| **TP2.3** | CNN | Neural style transfer (Gatys) + colour preservation | Artworks + photo | PyTorch, VGG19, Kornia |
| **TP2.4** | CNN | Image super-resolution (×2) | MNIST | TensorFlow / Keras |
| **TP3** | LSTM & Transformer | Autoregressive music generation | Bach Cello Suites (MIDI) | PyTorch Lightning, pretty_midi |

**Methods & techniques**
- manual forward / backward propagation, gradient descent, momentum
- autograd, `nn.Sequential` vs `nn.Module`, `DataLoader`, mini-batch training
- Adam, SGD, L-BFGS optimisers
- BCE, cross-entropy, MSE, Gram / mean-covariance style losses, total variation
- optimisation in input space: Deep Dream, adversarial examples, style transfer
- colour transfer by covariance matching (RGB / LAB)
- one-hot encoding, teacher forcing, causal masking, sinusoidal positional encoding
- early stopping, checkpointing, temperature sampling

---

## TP1: Multi-Layer Perceptron
📁 `TPs/TP1/`

Binary classification of two concentric noisy circles (`make_circles`, 1 000 points, standardised inputs), a dataset that is not linearly separable and therefore needs a hidden layer.

### 1. MLP from scratch in NumPy
`Lab-DL__MLP_CLASS_#python-fromscratch_#2026-09-15_#student.ipynb`

A simple MLP network (ReLU hidden layer, sigmoid output) written as a Python class, with **every step coded by hand in matrix form**:
- forward propagation (`Z = XW + b`, batch of `m` examples as rows)
- binary cross-entropy cost
- backward propagation (`dZ2 = A2 − Y`, `dW = AᵀdZ / m`, …)
- parameter updates with **plain gradient descent** and **momentum** (bonus)

Full-batch training, 5 000 epochs, learning rate 0.1, 80/20 train/test split.
**Result:** ~89 % train / ~90 % test accuracy, with train and test curves following each other (no over-fitting).

### 2. The same MLP in PyTorch (three ways)
`Lab_DL_MLP_CLASS_pytorch_model123_2026_09_15_makecircle_Tom_Cuel.ipynb`

A deeper MLP network (ReLU, sigmoid output), written three times to go from low-level to idiomatic PyTorch:
| Model | Parameters | Loss | Update |
|---|---|---|---|
| **1: raw tensors** | `W`, `b` created by hand with `requires_grad=True` | BCE written by hand (with clamping against `log(0)`) | manual in-place update from `.grad` inside `torch.no_grad()`, gradients reset by hand |
| **2: `nn.Sequential`** | `nn.Linear` + `nn.ReLU` + `nn.Sigmoid` | `nn.BCELoss` | `optim.SGD`, `zero_grad / backward / step` |
| **3: `nn.Module` subclass** | layers in `__init__`, equations in `forward` | `nn.BCELoss` | `optim.SGD` |

Main takeaway: **autograd** replaces the hand-written backward pass of part 1, and `torch.nn` / `torch.optim` replace the hand-written layers and updates.

---

## TP2: Convolutional Neural Networks
📁 `TPs/TP2/`

### 2.1 CNN classification: MNIST & CIFAR-10
`Lab-DL_CNN_classification_#student.ipynb`

Small CNNs built with `nn.Sequential` (`Conv2d` 3×3 `padding='same'` + `ReLU` + `MaxPool2d` + `Flatten` + `Linear`), trained with **Adam** and `CrossEntropyLoss` (softmax included in the loss, the network outputs logits), mini-batches through `DataLoader`. Reduced training sets for speed.

| Dataset | Architecture | Training set | Train acc. | Test acc. |
|---|---|---|---|---|
| MNIST (28×28×1) | 2 conv + 1 pool + FC | 2 000 images, 10 epochs | 99.2 % | **93.0 %** |
| CIFAR-10 (32×32×3) | 4 conv + 3 pool + FC | 5 000 images, 25 epochs | 67.9 % | **49.9 %** |

The gap between the two datasets illustrates how much harder natural colour images are than digits for a small network trained on few examples (and the over-fitting it causes). 
The 32 learned first-layer filters are then displayed and are, as expected, hard to interpret directly, which motivates the next lab.

### 2.2 Deep Dream & adversarial examples
`Lab-DL_CNN_Deep-Dream_#student.ipynb`

Both parts use a frozen **pre-trained VGG19** (torchvision, ImageNet weights) and optimise **the input image instead of the weights**: `requires_grad` on the image, `loss.backward()`, then a gradient step on the pixels.

- **Deep Dream:** gradient *ascent* on the mean squared activation of chosen layers of `vgg.features` (layers 21–22), with gradient normalisation (zero mean, unit std) and clipping to the valid normalised range. The network's learned patterns progressively appear in the image.
- **Adversarial examples:** gradient ascent on the log-softmax probability of a target class (*reflex camera*, ImageNet class 759) starting from a cat image (*Egyptian cat*, 285). After a few dozen small steps the network predicts the target class while the image still looks like a cat to a human.

### 2.3 Neural style transfer
`Lab-DL_CNN_style-transfer_#student.ipynb`

Optimisation of an image (initialised as content + noise) with **L-BFGS** so that it keeps the content of a photo and takes the style of an artwork (Van Gogh, Hokusai, Hiroshige).

- **Feature extraction:** `create_feature_extractor` on VGG19, returning `relu1_1 … relu5_1` (style) and `relu4_2` (content).
- **Losses implemented:**
  - content loss: MSE between feature maps
  - style loss: two variants: **Gram matrices**, or **mean + covariance** (`MuSigma`) of the feature maps
  - **total-variation** regulariser for smoothness
- **Colour preservation:** before the transfer, the colour palette of the content image is moved onto the style image by matching mean and covariance of the pixel colours (`√Σₜ · √Σₛ⁻¹`, matrix square roots via `torch.linalg.eigh`), tested in **RGB and LAB** colour spaces (Kornia).
- **Bonus, peace dove:** the hardest style (a black-and-white sketch). The content photo is first turned into a sketch (Kornia **Canny** edges, dilation, slight blur), then stylised, then recoloured with the dove's palette.

### 2.4 Super-resolution (optional)
`Lab-DL_CNN_Super-resolution_#student.ipynb`

Free-design CNN in **Keras** that upsamples 14×14 MNIST digits back to 28×28 (factor δ = 2). Training pairs are built from the data itself: input = image subsampled one pixel out of two, target = original image.

Architecture: two 3×3 conv layers at low resolution + `UpSampling2D` (bilinear) + three conv layers at high resolution (sigmoid output, pixels in [0, 1]). MSE loss, Adam, 20 epochs, 5 000 images.

| Method | Test MSE (per pixel) |
|---|---|
| Bilinear interpolation | 0.0227 |
| **CNN** | **0.0048** |

The CNN is about 5× better than interpolation and produces visibly sharper strokes. 

---

## TP3: Language model for music: LSTM vs Transformer
📁 `TPs/TP3/`
`Lab_DL__Transformer_GEN_realLM_simple__pytorch_lightning__bach__2026_10_09__student_clean.ipynb`

Training an **autoregressive language model on music** then sampling it to compose a new piece (One-to-Many).

**Data pipeline**
- MIDI files read with `pretty_midi`: only the **pitch** of each note is kept (up to 1 000 notes per file)
- each note encoded as a **one-hot vector** over 79 pitches
- sliding windows of 100 notes: input `x = notes[t : t+100]`, target `y = notes[t+1 : t+101]` (sequence shifted by one step, i.e. teacher forcing): **20 901 training sequences**

**Models** (both output logits over the 79 notes at every time step)
| | Model 1: LSTM | Model 2: Transformer (decoder-only) |
|---|---|---|
| Structure | 3 stacked `nn.LSTM` (32 units) with dropout 0.3, then Linear + tanh + dropout, then Linear | Linear embedding (d_model = 80) + **sinusoidal positional encoding** (coded by hand) + 4 `TransformerEncoderLayer` (2 heads, FFN 128, GELU) with a **causal mask** + Linear |
| Parameters | 35 k | 200 k |

**Training** with **PyTorch Lightning**: the `nn.Module` is wrapped in a `LightningModule` (cross-entropy loss, accuracy logging, Adam lr 1e-3), 90/10 train/validation split, `EarlyStopping` (patience 3) and `ModelCheckpoint` on the validation loss, GPU (CUDA) training.

**Generation**
- first note drawn from the empirical note distribution of the corpus
- autoregressive loop: predict + softmax with **temperature** + sample with `torch.multinomial` + append the note as input for the next step
- the generated sequence is written to a new MIDI file (cello program) and synthesised to audio in the notebook

The generated melodies reproduce recognisable Bach-like patterns (arpeggios, repeated motifs, scale runs).