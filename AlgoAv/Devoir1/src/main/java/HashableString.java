import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class HashableString implements FamilyHashable {

    public String string;

    public HashableString(String string) {
        this.string = string;
    }
    private static byte[] bytesOfInt(int seed) {
        byte[] seedEncoding = new byte[] {
                (byte) (seed & 0xff),
                (byte) ((seed & 0xff00) >> 8),
                (byte) ((seed & 0xff0000) >> 16),
                (byte) ((seed & 0xff000000) >> 24),
        };
        return seedEncoding;
    }
    private static long longOfDigest(byte[] digest) {
        long hash = 0;
        for (int i = 0; i < 8; i++) {
            hash = (hash << 8) + Math.floorMod(digest[i],0xff);
        }
        return hash;
    }
    @Override
    public long hashCode(int seed) {
        MessageDigest digest = null;
        try {
            digest = MessageDigest.getInstance("SHA-256");
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            System.exit(1);
        }
        digest.update(bytesOfInt(seed));
        digest.update(this.string.getBytes());
        return longOfDigest(digest.digest());
    }
    public String getString() { return string; }
    public boolean equals (Object o) {
        if (!(o instanceof HashableString)) return false;
        HashableString oAsHashString = (HashableString) o;
        return this.string.equals(oAsHashString.string);
    }

    public String toString(){
        return this.string;
    }
}