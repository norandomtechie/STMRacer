from PIL import Image
import os, glob

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED   = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE  = (0, 0, 255)

def convert_png_to_bmp():
    for filename in glob.glob (os.path.join (os.getcwd(), "*.png")):
        png_img = Image.open (filename)
        bmp_img = Image.new('RGB',png_img.size,(255,255,255))
        bmp_img.paste(png_img,(0,0),png_img)
        bmp_img.save (filename [:filename.index ('.')] + ".bmp")
        os.remove (filename)

def print_bitmaps():
    files = glob.glob (os.path.join (os.getcwd(), "*.bmp"))
    for file in files:
        im = Image.open (file)
        pixels = list (im.getdata())
        width, height = im.size
        i = 0
        tab_space = len ("char {}[] = ".format(os.path.basename (file)))
        print ("char {}[] = ".format(os.path.basename (file) [:os.path.basename (file).index ('.')]), end="", flush=True)
        print ("{", end="", flush=True)
        index_list = []
        while i != 1024:
            for j in range (i, i + 31):
                # print ("1," if pixels [j] == BLACK else "0,", end="", flush=True)
                if pixels [j] == BLACK:
                    index_list.append (j)
            if i + 32 == 1024:
                # print ("1" if pixels [i + 31] == BLACK else "0", end="", flush=True)
                if pixels [j] == BLACK:
                    index_list.append (j)
            else:
                # print ("1," if pixels [i + 31] == BLACK else "0,", end="", flush=True)
                if pixels [j] == BLACK:
                    index_list.append (j)
                # print ("")
                # print (" " * (int (tab_space) - 3), end="", flush=True)
            i += 32
        if len (index_list) > 2:
            for elm in index_list [:-1]:
                print (elm, end="", flush=True)
                print (",", end="", flush=True)
            print (index_list [-1], end="", flush=True)
        else:
            print ("0", end="", flush=True)
        print ("};\n")


if __name__ == "__main__":
    convert_png_to_bmp()
    print_bitmaps()
