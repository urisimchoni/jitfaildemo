
public class Hello {
    public static void main(String[] args) {
        AManyFields amf = new AManyFields();
        MyAgent.analyzeObj(amf);
        BManyFields bmf = new BManyFields();
        MyAgent.analyzeObj(bmf);

        int sum=0;
        sum+=amf.getSum();
        sum+=bmf.getSum();
        System.out.printf("Sum is %d\n",sum);
    }
}
