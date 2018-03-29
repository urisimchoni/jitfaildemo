public class ManyFields {
    public Pojo field1;

    public ManyFields() {
        field1 = new Pojo();
    }

    public int getSum() {
        int sum = 0;
        sum += field1.i;

        return sum;
    }
}
