package fr.licinfo;

import com.google.gson.Gson;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.List;

public class OpenPitInstance {

  public double ore_value;
  public int nbr_blocks;
  public List<Block> blocks;
  public OpenPitInstance() {};


  public static class Block {
    public int uid;
    public double ore;
    public double cost;
    public List<Integer> blocks_above;
    public boolean is_removable;
    public List<Point> polygon;
    public Block() {};

    public double getDensity() { return this.ore / this.cost; }
  }

  public static class Point {
    public double x;
    public double y;
    public Point() {}
  }

  public static Gson gson = new Gson();

  public static OpenPitInstance readFromJsonFile(String filename)
    throws FileNotFoundException
  {
    FileReader input = new FileReader(filename);
    return gson.fromJson(input,OpenPitInstance.class);
  }

}
