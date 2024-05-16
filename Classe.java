import java.util.List;
import java.util.ArrayList;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;

class Personagem{
    private String id;
    private String nome;
    private List<String> nome_alternativo;
    private String casa;
    private String ancestral;
    private String especie;
    private String patronus;
    private Boolean staff;
    private String estudante;
    private String nomeator;
    private Boolean vivo;
    private String atoresalternativos;
    private Date dianascimento;
    private int anonascimento;
    private String corolho;
    private String sexo;
    private String corcabelo;
    private Boolean bruxo;

    public Personagem(){
        nome_alternativo = new ArrayList<>();
        this.staff = false;
        this.vivo=false;
        this.bruxo=false;
    }
    // Setters
    public void setId(String id) {
        this.id = id;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setCasa(String casa) {
        this.casa = casa;
    }

    public void setNomeAlternativo(List<String> nomeAlternativo) {
        this.nome_alternativo = new ArrayList<>(nomeAlternativo);
    }

    public void addNomeAlternativo(String nomeAlternativo) {
        this.nome_alternativo.add(nomeAlternativo);
    }

    public void setAncestral(String ancestral) {
        this.ancestral = ancestral;
    }

    public void setEspecie(String especie) {
        this.especie = especie;
    }

    public void setPatronus(String patronus) {
        this.patronus = patronus;
    }

    public void setStaff(boolean staff) {
        this.staff = staff;
    }

    public void setEstudante(String estudante) {
        this.estudante = estudante;
    }

    public void setNomeator(String nomeator) {
        this.nomeator = nomeator;
    }

    public void setVivo(boolean vivo) {
        this.vivo = vivo;
    }
    public void setAtorAlternativo(String dados){
            dados = dados.replace("[", "").replace("]", "").replace("'", "").trim();
            if (!dados.isEmpty()) {
                String[] nomes = dados.split(", ");
                for (String nome : nomes) {
                    this.nome_alternativo.add(nome);
                }
            }
    }

    public void setDianascimento(String dianascimentoStr) {
        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
        try {
            this.dianascimento = sdf.parse(dianascimentoStr);
        } catch (Exception e) {
            System.out.println("Formato de data inválido: " + e.getMessage());
            this.dianascimento = null; 
        }
    }

    public void setAnonascimento(int anonascimento) {
        this.anonascimento = anonascimento;
    }

    public void setCorolho(String corolho) {
        this.corolho = corolho;
    }

    public void setSexo(String sexo) {
        this.sexo = sexo;
    }

    public void setCorcabelo(String corcabelo) {
        this.corcabelo = corcabelo;
    }

    public void setBruxo(boolean bruxo) {
        this.bruxo = bruxo;
    }
// Getters
        public String getId() {
            return id;
        }
    
        public String getNome() {
            return nome;
        }
    
        public String getCasa() {
            return casa;
        }
    
        public List<String> getNomeAlternativo() {
            return new ArrayList<>(nome_alternativo);
        }
    
        public String getAncestral() {
            return ancestral;
        }
    
        public String getEspecie() {
            return especie;
        }
    
        public String getPatronus() {
            return patronus;
        }
    
        public boolean isStaff() {
            return staff;
        }
    
        public String isEstudante() {
            return estudante;
        }
    
        public String getNomeator() {
            return nomeator;
        }
    
        public boolean isVivo() {
            return vivo;
        }
        public String getatoralternativo(){
            return atoresalternativos;
        }
    
        public String getDianascimento() {
            SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
            if (this.dianascimento != null) {
                return sdf.format(this.dianascimento);
            } else {
                return "Data de nascimento não disponível";
            }
            }
    
        public int getAnonascimento() {
            return anonascimento;
        }
    
        public String getCorolho() {
            return corolho;
        }
    
        public String getSexo() {
            return sexo;
        }
    
        public String getCorcabelo() {
            return corcabelo;
        }
    
        public boolean isBruxo() {
            return bruxo;
        }
    

        public void ler(String codigo){
            try (BufferedReader br = new BufferedReader(new FileReader("/tmp/characters.csv"))) {
                String linha;
                String[] campos;
                boolean personagemEncontrado = false;
        
                while ((linha = br.readLine()) != null) {
                    campos = linha.split(";");
                    if (campos[0].equals(codigo)) {
                        setId(campos[0]);
                        setNome(campos[1]);
                        addNomeAlternativo(campos[2]);
                        setCasa(campos[3]);
                        setAncestral(campos[4]);
                        setEspecie(campos[5]);
                        setPatronus(campos[6]);
                        setStaff(Boolean.parseBoolean(campos[7]));
                        setEstudante(campos[8]);
                        setNomeator(campos[9]);
                        setVivo(Boolean.parseBoolean(campos[10]));
                        setAtorAlternativo(campos[11]);
                        setDianascimento(campos[12]);
                        setAnonascimento(Integer.parseInt(campos[13]));
                        setCorolho(campos[14]);
                        setSexo(campos[15]);
                        setCorcabelo(campos[16]);
                        setBruxo(Boolean.parseBoolean(campos[17]));
                        
                        personagemEncontrado = true;
                        break; 
                    }
                }
        
                if (!personagemEncontrado) {
                    System.out.println("Personagem não encontrado.");
                }
            } catch (IOException | NumberFormatException e) {
                System.out.println("Erro ao ler arquivo ou formatar: " + e.getMessage());
            }
        }
public void imprimir(){
    MyIO.println("["+getId()+" ## "+getNome()+" ## "+getNomeAlternativo()+" ## "+getCasa()+" ## "+getAncestral()+" ## "+getEspecie()+" ## "+getPatronus()+" ## "+isStaff()+" ## "+isEstudante()+" ## "+getNomeator()+" ## "+isVivo()+" ## "+getDianascimento()+" ## "+getAnonascimento()+" ## "+getCorolho()+" ## "+getSexo()+" ## "+getCorcabelo()+" ## "+isBruxo()+"]");
}
}


class Classe{
    public static void main(String args []){
        String linha=MyIO.readLine();
        while(!linha.equals("FIM")){
            Personagem personagem = new Personagem();
            personagem.ler(linha);
            personagem.imprimir();
            linha=MyIO.readLine();
            }
    }
}