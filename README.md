![image0](https://github.com/user-attachments/assets/947dd461-b489-4bf0-adfd-d00a9adaa266)


![Sequence01_1-ezgif com-crop](https://github.com/user-attachments/assets/17ba8636-67c3-454f-b6f8-934553cf538f)
_Vortex GUI shown above. Release date December 2024_

Vortex is a chess bot implemented in C++ and utilizing libtorch for efficient computation. It leverages a feedforward neural network architecture to evaluate board states and make strategic moves based on real-time assessments. The model takes in a tensor representation of the chessboard, incorporating both the positions of the pieces and the current score, to predict optimal moves.

The bot employs advanced techniques for preprocessing board states into a one-hot encoded format. It includes robust validation mechanisms to ensure legality of moves, making it adaptable for both standard and custom chess variants.

Vortex showcases the capability of neural networks to engage in strategic gameplay, providing insights into move selection and game dynamics. It serves as a framework for further research and development in LLM applied to chess, with potential for enhancements such as reinforcement learning and advanced evaluation metrics.

# Customisability

Vortex can mimic various chess player styles, allowing users to fine-tune the bot's behavior to reflect different strategies and approaches to the game. Through customizable hyperparameters, users can modify the model's aggressiveness, positional play, and defensive tendencies, enabling it to simulate a range of playing styles—from tactical attackers to positional defenders. Additionally, the architecture supports the integration of user-defined heuristics and evaluation functions, providing a flexible framework for enhancing decision-making processes. This level of customization not only allows players to tailor the bot to their preferences but also facilitates experimentation with different strategies, making Vortex a powerful tool for both training and analysis in chess.

# Windows Installation:
1) Make sure you have Python 3.8 or later installed


3) Can be downloaded from here:
   
   https://www.python.org/downloads/
   
4) Go to https://pytorch.org/ and download the latest Libtorch.

   This is the one I downloaded (the release one):
   
![image](https://github.com/user-attachments/assets/ac6a0d50-837d-4ed8-8758-9d9d2666822e)


6) Tested Pytorch: Stable 2.4.1 C++/Java CUDA 12.1 (CUDA is not required)
   
   If you want CUDA, make sure you download CUDA first before installing Pytorch from here:
   
   https://developer.nvidia.com/cuda-toolkit-archive
   
   Download the CUDA version supported by the Pytorch version you want

7) Once downloaded, navigate to libtorch-win-shared-with-deps-2.4.1+cu124.zip\libtorch\lib (your version may be different)

   Copy all of the files ending with .dll (dont copy any of the other files):

![image](https://github.com/user-attachments/assets/1891d8e4-1d29-4faa-acae-7ae3d96788ef)

8) Navigate where you want Vortex to be and run: ```git clone https://github.com/AmmarIrfanDev/Vortex.git```

9) Open ```Vortex.sln``` (you need Visual Studio 2022 installed if you have not done so already)

10) Build the solution once in Debug and Release.

11) Paste all of the dll files in Vortex/x64/Release and Vortex/x64/Debug

12) Enjoy using Vortex!
